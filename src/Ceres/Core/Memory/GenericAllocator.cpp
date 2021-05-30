#include "GenericAllocator.h"

#include <cassert>
#include <new>
#include "Ceres/Core/Memory/Align.h"

namespace Ceres
{
    // Generic allocator

    GenericAllocator::GenericAllocator(SizeType size, uint32 maxBlocks)
        : _genericSize(size), _numBlocks(maxBlocks)
    {
        // Allocate a chunk of memory large enough for the block table and our actual data
        const SizeType blockSize = sizeof(BlockEntry) * maxBlocks;
        const SizeType totalSize = blockSize + _genericSize;
        _blockTable = reinterpret_cast<BlockEntry*>(allocAligned(totalSize, alignof(BlockEntry)));
        _genericData = reinterpret_cast<uint8*>(_blockTable) + blockSize;

        // Initialize the block table entries
        for (uint32 i = 0; i < _numBlocks; i++)
        {
            new (&_blockTable[i]) BlockEntry();
        }

        // Store one big free chunk at the start of our generic data
        _freeHead = new (_genericData) FreeBlockEntry();
        _freeHead->nextFreeBlock = nullptr;
        _freeHead->size = _genericSize;
    }

    GenericAllocator::~GenericAllocator()
    {
        freeAligned(reinterpret_cast<uint8*>(_blockTable));
    }

    GenericAllocator::Handle GenericAllocator::allocate(SizeType size, SizeType alignment)
    {
        // First find if we have a block large enough to store our data
        FreeBlockSearchResult foundFreeBlock = findFreeBlock(size);
        if (foundFreeBlock.freeBlock != nullptr)
        {
            // Find if we have an open entry in our block table
            int32 blockIndex = findFirstUnusedBlockIndex();
            if (blockIndex != BlockEntry::INVALID_INDEX)
            {
                // Split the free block entry if needed
                if (foundFreeBlock.freeBlock->size > size)
                {
                    // Copy the data since it might get overwritten
                    const SizeType previousFreeSize = foundFreeBlock.freeBlock->size;
                    FreeBlockEntry* nextFreeBlockEntry = foundFreeBlock.freeBlock->nextFreeBlock;

                    // Insert a new block entry into the list
                    FreeBlockEntry* newFreeBlockEntry = new (reinterpret_cast<uint8*>(foundFreeBlock.freeBlock) + size) FreeBlockEntry();
                    newFreeBlockEntry->size = previousFreeSize - size;
                    newFreeBlockEntry->nextFreeBlock = nextFreeBlockEntry;

                    // If the previous block is null, then we're at the start of the list
                    if (foundFreeBlock.previousFreeBlock == nullptr)
                    {
                        _freeHead = newFreeBlockEntry;
                    }
                    else
                    {
                        foundFreeBlock.previousFreeBlock->nextFreeBlock = newFreeBlockEntry;
                    }
                }
                else
                {
                    if (foundFreeBlock.previousFreeBlock == nullptr)
                    {
                        _freeHead = foundFreeBlock.freeBlock->nextFreeBlock;
                    }
                    else
                    {
                        foundFreeBlock.previousFreeBlock->nextFreeBlock = foundFreeBlock.freeBlock->nextFreeBlock;
                    }
                }

                // Assign the block entry to our new data
                BlockEntry& blockEntry = _blockTable[blockIndex];
                blockEntry.referenceCount = 0;
                blockEntry.data = reinterpret_cast<uint8*>(foundFreeBlock.freeBlock);
                blockEntry.size = size;
                blockEntry.offset = alignment;

                return Handle(*this, blockIndex, blockEntry.id);
            }
        }

        return Handle();
    }

    void GenericAllocator::defragment(uint32)
    {
        // Todo - defragment a chunk of memory!
    }

    GenericAllocator::BlockEntry* GenericAllocator::findBlockEntry(const Handle& handle) const
    {
        if (handle._allocator == this)
        {
            // Find the entry corresponding to the handle's index
            assert(handle._index < _numBlocks);
            BlockEntry& foundEntry = _blockTable[handle._index];

            // Verify that the handle is not stale
            if (foundEntry.id == handle._id)
            {
                return &foundEntry;
            }
        }

        return nullptr;
    }

    uint8* GenericAllocator::getData(const Handle& handle) const
    {
        if (const BlockEntry* foundEntry = findBlockEntry(handle))
        {
            return foundEntry->data;
        }

        return nullptr;
    }

    void GenericAllocator::incrementReferences(const Handle& handle)
    {
        if (BlockEntry* blockEntry = findBlockEntry(handle))
        {
            blockEntry->referenceCount++;
        }
    }

    void GenericAllocator::decrementReferences(const Handle& handle)
    {
        if (BlockEntry* blockEntry = findBlockEntry(handle))
        {
            if (--blockEntry->referenceCount == 0)
            {
                freeBlock(*blockEntry);
            }
        }
    }

    int32 GenericAllocator::findFirstUnusedBlockIndex() const
    {
        for (uint32 i = 0; i < _numBlocks; i++)
        {
            const BlockEntry& blockEntry = _blockTable[i];

            if (blockEntry.data == nullptr)
            {
                return static_cast<int32>(i);
            } 
        }

        return BlockEntry::INVALID_INDEX;
    }

    void GenericAllocator::freeBlock(BlockEntry& entry)
    {
        static const auto tryMergeBlocks = [](FreeBlockEntry* block1, FreeBlockEntry* block2) -> bool
        {
            // Check if the blocks are touching
            if ((reinterpret_cast<uint8*>(block1) + block1->size) == reinterpret_cast<uint8*>(block2))
            {
                block1->nextFreeBlock = block2->nextFreeBlock;
                block1->size += block2->size;
                return true;
            }

            return false;
        };

        assert(entry.referenceCount == 0);

        // Create a new free block entry where the block data used to live
        FreeBlockEntry* newFreeBlock = new (entry.data) FreeBlockEntry();
        newFreeBlock->size = entry.size;

        // Find the free blocks on either side of this used block
        FreeBlockSearchResult foundFreeBlocks = findFreeBlock(entry);

        // If the next free block is null then this block is at the end
        // We should try to merge it with the next entry, and insert it to the list if we can't
        if (foundFreeBlocks.freeBlock != nullptr && !tryMergeBlocks(newFreeBlock, foundFreeBlocks.freeBlock))
        {
            newFreeBlock->nextFreeBlock = foundFreeBlocks.freeBlock;
        }

        // If the previous block is null then the new free block is the head
        if (foundFreeBlocks.previousFreeBlock == nullptr)
        {
            _freeHead = newFreeBlock;
        }
        else if (!tryMergeBlocks(foundFreeBlocks.previousFreeBlock, newFreeBlock))
        {
            // If we can't merge the blocks insert the new block into the list
            foundFreeBlocks.previousFreeBlock->nextFreeBlock = newFreeBlock;
        }

        // Clean the block entry and increment its ID
        entry.id++;
        entry.data = nullptr;
        entry.size = 0;
        entry.offset = 0;
    }

    GenericAllocator::FreeBlockSearchResult GenericAllocator::findFreeBlock(SizeType size) const
    {
        FreeBlockSearchResult result;
        result.freeBlock = _freeHead;
        result.previousFreeBlock = nullptr;

        // Find the first free block entry (and the preceeding block entry)
        while (result.freeBlock != nullptr)
        {
            if (result.freeBlock->size >= size)
            {
                return result;
            }

            result.previousFreeBlock = result.freeBlock;
            result.freeBlock = result.freeBlock->nextFreeBlock;
        }

        return result;
    }

    GenericAllocator::FreeBlockSearchResult GenericAllocator::findFreeBlock(const BlockEntry& entry) const
    {
        FreeBlockSearchResult result;
        result.freeBlock = _freeHead;
        result.previousFreeBlock = nullptr;

        // Find the free block entries on either side of the used block entry
        while (result.freeBlock != nullptr)
        {
            if (reinterpret_cast<SizeType>(result.previousFreeBlock) < reinterpret_cast<SizeType>(entry.data) &&
                reinterpret_cast<SizeType>(result.freeBlock) > reinterpret_cast<SizeType>(entry.data))
            {
                return result;
            }

            result.previousFreeBlock = result.freeBlock;
            result.freeBlock = result.freeBlock->nextFreeBlock;
        }

        return result;
    }


    // GenericAllocator::Handle

    GenericAllocator::Handle::Handle(GenericAllocator& allocator, uint32 index, uint32 id)
        : _allocator(&allocator), _index(index), _id(id)
    {
        _allocator->incrementReferences(*this);
    }

    GenericAllocator::Handle::~Handle()
    {
        clear();
    }

    bool GenericAllocator::Handle::isValid() const
    {
        if (_allocator)
        {
            return _allocator->findBlockEntry(*this) != nullptr;
        }

        return false;
    }

    uint8* GenericAllocator::Handle::getData() const
    {
        if (_allocator)
        {
            return _allocator->getData(*this);
        }

        return nullptr;
    }

    void GenericAllocator::Handle::clear()
    {
        if (_allocator)
        {
            _allocator->decrementReferences(*this);
        }

        _allocator = nullptr;
        _index = 0;
        _id = 0;
    }


    // GenericAllocator::WeakHandle

    GenericAllocator::Handle GenericAllocator::WeakHandle::pin() const
    {
        if (_allocator)
        {
            return Handle(*_allocator, _index, _id);
        }

        return Handle();
    }
}
