#include "GenericAllocator.h"

#include <cassert>

namespace Ceres
{
    GenericAllocator::GenericAllocator(SizeType size, SizeType numBlocks)
        : _allocator(size + sizeof(DataBlockEntry) * numBlocks), _maxNumBlocks(numBlocks), _numUsedBlocks(0)
    {
        // Allocate a chunk of memory to store the block table
        _dataBlockTable = reinterpret_cast<DataBlockEntry*>(_allocator.allocateBlock(sizeof(DataBlockEntry) * _maxNumBlocks));

        // Fill the block table with empty entries
        for (SizeType i = 0; i < _maxNumBlocks; i++)
        {
            _dataBlockTable[i].data = nullptr;
            _dataBlockTable[i].size = 0;
            _dataBlockTable[i].id = 0;
            _dataBlockTable[i].referenceCount = 0;
        }
    }

    GenericAllocator::Handle GenericAllocator::allocateBlock(SizeType size)
    {
        if (_numUsedBlocks < _maxNumBlocks)
        {
            for (SizeType i = 0; i < _maxNumBlocks; i++)
            {
                // Find the first unused block in our table
                if (_dataBlockTable[i].data == nullptr)
                {
                    _dataBlockTable[i].data = _allocator.allocateBlock(size);
                    if (!_dataBlockTable[i].data)
                    {
                        // If we failed to allocate our new memory, exit immediately
                        break;
                    }
                    _dataBlockTable[i].size = size;

                    // Increment the number of used blocks for bookkeeping
                    _numUsedBlocks++;
                    return GenericAllocator::Handle(*this, i, _dataBlockTable[i].id);
                }
            }
        }

        // If allocation failed (either due to using all of our blocks or
        // the allocator running out of memory) return a null handle
        return GenericAllocator::Handle();
    }

    SizeType GenericAllocator::defragmentBlocks(SizeType numBlocks)
    {
        SizeType numBlocksDefragmented = 0;
        SizeType numBlocksChecked = 0;

        for (SizeType i = 0; i < _maxNumBlocks; i++)
        {
            if (_dataBlockTable[i].data != nullptr)
            {
                // Count the number of blocks that are in use so we can early out
                // if we've already checked all used blocks
                numBlocksChecked++;

                // Track the previous address of the data before the shift
                const uint8* previousBlockAddress = _dataBlockTable[i].data;
                _dataBlockTable[i].data = _allocator.tryShiftBlock(_dataBlockTable[i].data, _dataBlockTable[i].size);

                // If the address changed then we've successfully defragmented a block
                if (previousBlockAddress != _dataBlockTable[i].data)
                {
                    numBlocksDefragmented++;
                }

                // Early out if we've checked the number of blocks we need or all of them
                if (numBlocksChecked >= _numUsedBlocks || numBlocksDefragmented >= numBlocks)
                {
                    break;
                }
            }
        }

        return numBlocksDefragmented;
    }

    GenericAllocator::DataBlockEntry* GenericAllocator::getBlockEntry(const Handle& handle) const
    {
        if (handle._allocator == this && handle._index < _maxNumBlocks)
        {
            DataBlockEntry* blockEntry = &_dataBlockTable[handle._index];
            if (blockEntry->id == handle._id)
            {
                return blockEntry;
            }
        }

        return nullptr;
    }

    uint8* GenericAllocator::getBlockData(const Handle& handle) const
    {
        if (const DataBlockEntry* blockEntry = getBlockEntry(handle))
        {
            return blockEntry->data;
        }

        return nullptr;
    }

    void GenericAllocator::incrementReferenceCount(const Handle& handle)
    {
        if (DataBlockEntry* blockEntry = getBlockEntry(handle))
        {
            blockEntry->referenceCount++;
        }
    }

    void GenericAllocator::decrementReferenceCount(const Handle& handle)
    {
        if (DataBlockEntry* blockEntry = getBlockEntry(handle))
        {
            assert(blockEntry->referenceCount > 0);

            if (--blockEntry->referenceCount == 0)
            {
                // If our reference count has reached zero, deallocate the data
                // and free the block in the table
                _allocator.freeBlock(blockEntry->data, blockEntry->size);
                blockEntry->data = nullptr;
                blockEntry->size = 0;
                blockEntry->id++;
                _numUsedBlocks--;
            }
        }
    }


    GenericAllocator::Handle::Handle()
        : _allocator(nullptr), _index(0), _id(0)
    {};

    GenericAllocator::Handle::Handle(const Handle& other)
        : _allocator(other._allocator), _index(other._index), _id(other._id)
    {
        if (_allocator)
        {
            _allocator->incrementReferenceCount(*this);
        }
    }

    GenericAllocator::Handle::Handle(Handle&& other)
        : _allocator(other._allocator), _index(other._index), _id(other._id)
    {
        // Because we're moving the underlying data, no reference counts should've changed
        other._allocator = nullptr;
        other._index = 0;
        other._id = 0;
    }

    GenericAllocator::Handle::~Handle()
    {
        if (_allocator)
        {
            _allocator->decrementReferenceCount(*this);
        }
    }

    GenericAllocator::Handle& GenericAllocator::Handle::operator=(const Handle& other)
    {
        // If these handles refer to the exact same object already we can skip
        // everything and avoid doing reference count changes
        if (*this != other)
        {
            // We have to decrement our previous reference count (if any)
            if (_allocator)
            {
                _allocator->decrementReferenceCount(*this);
            }

            _allocator = other._allocator;
            _index = other._index;
            _id = other._id;

            // And increment our new reference count (if any)
            if (_allocator)
            {
                _allocator->incrementReferenceCount(*this);
            }
        }

        return *this;
    }

    GenericAllocator::Handle& GenericAllocator::Handle::operator=(Handle&& other)
    {
        // If these handles are the same we can avoid some reference count changes
        // (like in copy assignment)
        if (*this != other)
        {
            if (_allocator)
            {
                _allocator->decrementReferenceCount(*this);
            }

            _allocator = other._allocator;
            _index = other._index;
            _id = other._id;

            other._allocator = nullptr;
            other._index = 0;
            other._id = 0;
        }
        // We still expect that the other object gets zeroed out though
        else
        {
            other.clear();
        }

        return *this;
    }

    bool GenericAllocator::Handle::operator==(const Handle& other) const
    {
        return (_allocator == other._allocator) && (_index == other._index) && (_id == other._id);
    }

    bool GenericAllocator::Handle::isExplicitlyNull() const
    {
        return _allocator == nullptr;
    }

    uint8* GenericAllocator::Handle::get() const
    {
        if (_allocator)
        {
            return _allocator->getBlockData(*this);
        }

        return nullptr;
    }

    void GenericAllocator::Handle::clear()
    {
        if (_allocator)
        {
            _allocator->decrementReferenceCount(*this);
        }

        _allocator = nullptr;
        _index = 0;
        _id = 0;
    }

    GenericAllocator::Handle::Handle(GenericAllocator& allocator, SizeType index, SizeType id)
        : _allocator(&allocator), _index(index), _id(id)
    {
        _allocator->incrementReferenceCount(*this);
    }


    GenericAllocator::WeakHandle::WeakHandle()
        : _allocator(nullptr), _index(0), _id(0)
    {}

    GenericAllocator::WeakHandle::WeakHandle(const WeakHandle& other)
        : _allocator(other._allocator), _index(other._index), _id(other._id)
    {}

    GenericAllocator::WeakHandle::WeakHandle(const Handle& other)
        : _allocator(other._allocator), _index(other._index), _id(other._id)
    {}

    GenericAllocator::WeakHandle& GenericAllocator::WeakHandle::operator=(const WeakHandle& other)
    {
        _allocator = other._allocator;
        _index = other._index;
        _id = other._id;

        return *this;
    }

    GenericAllocator::WeakHandle& GenericAllocator::WeakHandle::operator=(const Handle& other)
    {
        _allocator = other._allocator;
        _index = other._index;
        _id = other._id;

        return *this;
    }

    bool GenericAllocator::WeakHandle::operator==(const WeakHandle& other) const
    {
        return (_allocator == other._allocator) && (_index == other._index) && (_id == other._id);
    }

    bool GenericAllocator::WeakHandle::isExplicitlyNull() const
    {
        return _allocator == nullptr;
    }

    GenericAllocator::Handle GenericAllocator::WeakHandle::pin() const
    {
        if (_allocator)
        {
            return Handle(*_allocator, _index, _id);
        }

        return Handle();
    }
}
