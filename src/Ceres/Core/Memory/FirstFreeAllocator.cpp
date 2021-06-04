#include "FirstFreeAllocator.h"

#include <cassert>
#include <cstring>
#include "Core/Memory/Align.h"

namespace Ceres
{
    FirstFreeAllocator::FirstFreeAllocator(SizeType size, SizeType alignment)
    {
        _data = allocAligned(size, alignment);

        // Create a free block entry at the start of the allocated memory
        _freeListHead = reinterpret_cast<FreeBlockEntry*>(_data);
        _freeListHead->size = size;
        _freeListHead->next = nullptr;
    }

    FirstFreeAllocator::~FirstFreeAllocator()
    {
        freeAligned(_data);
    }

    uint8* FirstFreeAllocator::allocateBlock(SizeType size)
    {
        // Ensure all allocated blocks are large enough to store a linked list entry
        assert(size >= sizeof(FreeBlockEntry));

        const FreeBlockSearchResult foundBlock = findFreeBlockOfSize(size);
        if (FreeBlockEntry* newUsedBlock = foundBlock.next)
        {
            if (newUsedBlock->size == size)
            {
                // If the free block is exactly the size of the allocated memory
                // just remove the free block from the list
                if (foundBlock.previous != nullptr)
                {
                    foundBlock.previous->next = newUsedBlock->next;
                }
                else
                {
                    _freeListHead = newUsedBlock->next;
                }
            }
            else
            {
                // We need to split the new block into a used and free portion
                // and add the free portion to the list
                FreeBlockEntry* newFreeBlock = reinterpret_cast<FreeBlockEntry*>(reinterpret_cast<uint8*>(newUsedBlock) + size);
                newFreeBlock->next = newUsedBlock->next;
                newFreeBlock->size = newUsedBlock->size - size;

                if (foundBlock.previous != nullptr)
                {
                    foundBlock.previous->next = newFreeBlock;
                }
                else
                {
                    _freeListHead = newFreeBlock;
                }
            }

            return reinterpret_cast<uint8*>(newUsedBlock);
        }

        return nullptr;
    }

    void FirstFreeAllocator::freeBlock(uint8* data, SizeType size)
    {
        // Check that the address is at least within the range of the allocator's memory
        assert(reinterpret_cast<SizeType>(data) >= reinterpret_cast<SizeType>(_data));

        // Write to a new free block entry at the start of the freed data
        FreeBlockEntry* newFreeBlock = reinterpret_cast<FreeBlockEntry*>(data);
        newFreeBlock->size = size;

        // Find the free blocks around the newly freed block
        FreeBlockSearchResult foundBlocks = findFreeBlocksAround(data);

        // If there is free block after the newly freed block and they can't be merged
        // insert it into the list
        if (foundBlocks.next && !FreeBlockEntry::tryMergeBlocks(newFreeBlock, foundBlocks.next))
        {
            newFreeBlock->next = foundBlocks.next;
        }
        else if (!foundBlocks.next)
        {
            newFreeBlock->next = nullptr;
        }

        // Do the same thing with the previous block and the newly freed block
        if (foundBlocks.previous && !FreeBlockEntry::tryMergeBlocks(foundBlocks.previous, newFreeBlock))
        {
            foundBlocks.previous->next = newFreeBlock;
        }
        else if (!foundBlocks.previous)
        {
            _freeListHead = newFreeBlock;
        }
    }

    uint8* FirstFreeAllocator::tryShiftBlock(uint8* data, SizeType size)
    {
        // Special search that finds two blocks to the left of the data
        FreeBlockEntry* leftFreeBlock = nullptr;
        FreeBlockEntry* consideredBlock = nullptr;
        FreeBlockEntry* rightFreeBlock = _freeListHead;
        while (rightFreeBlock && (reinterpret_cast<SizeType>(rightFreeBlock) < reinterpret_cast<SizeType>(data)))
        {
            leftFreeBlock = consideredBlock;
            consideredBlock = rightFreeBlock;
            rightFreeBlock = rightFreeBlock->next;
        }

        // If there is a block to the left of the data and it touches the data
        if (consideredBlock && data == (reinterpret_cast<uint8*>(consideredBlock) + consideredBlock->size))
        {
            // Copy the size of the free block since it will be overwritten
            const SizeType originalBlockSize = consideredBlock->size;

            // Shift the data left
            std::memmove(consideredBlock, data, size);
            data = reinterpret_cast<uint8*>(consideredBlock);

            // Move the free block to the right
            FreeBlockEntry* newFreeBlock = reinterpret_cast<FreeBlockEntry*>(reinterpret_cast<uint8*>(consideredBlock) + size);
            newFreeBlock->size = originalBlockSize;

            // Add the new block to the list
            if (rightFreeBlock && !FreeBlockEntry::tryMergeBlocks(newFreeBlock, rightFreeBlock))
            {
                newFreeBlock->next = rightFreeBlock;
            }
            else if (!rightFreeBlock)
            {
                newFreeBlock->next = nullptr;
            }

            if (leftFreeBlock)
            {
                leftFreeBlock->next = newFreeBlock;
            }
            else
            {
                _freeListHead = newFreeBlock;
            }
        }

        return data;
    }

    FirstFreeAllocator::FreeBlockSearchResult FirstFreeAllocator::findFreeBlockOfSize(SizeType size) const
    {
        FreeBlockSearchResult result;
        result.next = _freeListHead;
        result.previous = nullptr;

        // Find the first free block that can contain the requested number of bytes
        while (result.next && result.next->size < size)
        {
            result.previous = result.next;
            result.next = result.next->next;
        }

        return result;
    }

    FirstFreeAllocator::FreeBlockSearchResult FirstFreeAllocator::findFreeBlocksAround(uint8* data) const
    {
        FreeBlockSearchResult result;
        result.next = _freeListHead;
        result.previous = nullptr;

        // Find the free blocks surrounding the requested address
        while (result.next && reinterpret_cast<SizeType>(result.next) < reinterpret_cast<SizeType>(data))
        {
            result.previous = result.next;
            result.next = result.next->next;
        }

        return result;
    }

    bool FirstFreeAllocator::FreeBlockEntry::tryMergeBlocks(FreeBlockEntry* block1, FreeBlockEntry* block2)
    {
        assert(block1 && block2);

        // If the two blocks touch, increment block1's size by block2's size and replace block2 in the list
        if ((reinterpret_cast<uint8*>(block1) + block1->size) == reinterpret_cast<uint8*>(block2))
        {
            block1->size += block2->size;
            block1->next = block2->next;
            return true;
        }

        return false;
    }
}
