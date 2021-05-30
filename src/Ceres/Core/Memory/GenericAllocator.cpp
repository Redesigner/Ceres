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
    }

    GenericAllocator::~GenericAllocator()
    {
        freeAligned(reinterpret_cast<uint8*>(_blockTable));
    }

    GenericAllocator::Handle GenericAllocator::allocate(SizeType size, SizeType alignment)
    {
        // Todo: find the first free block of memory! Somehow...
        uint8* newBlock = _genericData;

        int32 blockIndex = findFirstFreeBlockIndex();

        if (blockIndex != BlockEntry::INVALID_INDEX)
        {
            BlockEntry& blockEntry = _blockTable[blockIndex];
            blockEntry.referenceCount = 0;
            blockEntry.data = newBlock;
            blockEntry.size = size;
            blockEntry.alignment = alignment;

            return Handle(*this, blockIndex, blockEntry.id);
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

    int32 GenericAllocator::findFirstFreeBlockIndex() const
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
        assert(entry.referenceCount == 0);

        entry.id++;
        entry.data = nullptr;
        entry.size = 0;
        entry.alignment = 0;
    }


    // GenericAllocator::Handle

    GenericAllocator::Handle::Handle(GenericAllocator& allocator, uint32 index, uint32 id)
        : _allocator(&allocator), _index(index), _id(id)
    {
        _allocator->incrementReferences(*this);
    }

    GenericAllocator::Handle::~Handle()
    {
        if (_allocator)
        {
            _allocator->decrementReferences(*this);
        }
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
