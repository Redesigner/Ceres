#include "StackAllocator.h"

#include <cassert>

#include "Ceres/Core/Memory/Align.h"

namespace Ceres
{
    StackAllocator::StackAllocator(SizeType size, SizeType alignment)
        : _head(0), _size(size)
    {
        _data = allocAligned(size, alignment);
    }

    StackAllocator::~StackAllocator()
    {
        freeAligned(_data);
    }

    uint8* StackAllocator::allocate(SizeType size, SizeType alignment)
    {
        SizeType offset = 0;
        uint8* newBlock = _data + _head;

        // If we're allocating a block with a non-byte alignment, offset so the address
        // is aligned
        if (alignment > 1)
        {
            offset = alignment - (reinterpret_cast<SizeType>(newBlock) % alignment);
            if (offset == alignment)
            {
                offset = 0;
            }
            newBlock += offset;
        }

        // If the new allocation would push our stack beyond the allocated space, fail
        if ((_head + offset + size) > _size)
        {
            return nullptr;
        }

        // Store the new aligned head
        _head += offset + size;

        return newBlock;
    }

    void StackAllocator::freeTo(SizeType marker)
    {
        assert(marker <= _head);
        _head = marker;
    }
}
