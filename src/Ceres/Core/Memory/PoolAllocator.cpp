#include "PoolAllocator.h"

#include <cassert>
#include "Ceres/Core/Memory/Align.h"

namespace Ceres
{
    PoolAllocator::PoolAllocator(SizeType blockSize, SizeType alignment, SizeType numBlocks)
    {
        // Ensure our blocks are large enough to store a single pointer
        assert(blockSize >= sizeof(uint8*));

        // Allocate our data blocks
        _data = allocAligned(blockSize * numBlocks, alignment);

        // Store the address of the next free block at the start of each block
        for (SizeType i = 0; i < (numBlocks - 1); i++)
        {
            *reinterpret_cast<uint8**>(_data + i * blockSize) = _data + (i + 1) * blockSize;
        }
        // Mark the last free element as such via nullptr
        *reinterpret_cast<uint8**>(_data + (numBlocks - 1) * blockSize) = nullptr;

        // Keep the first free element
        _freeHead = _data;
    }

    PoolAllocator::~PoolAllocator()
    {
        freeAligned(_data);
    }

    uint8* PoolAllocator::allocate()
    {
        // Make sure we're not out of free blocks
        if (_freeHead == nullptr)
        {
            return nullptr;
        }

        // Grab the first free block and pull it from the list
        uint8* block = _freeHead;
        _freeHead = *reinterpret_cast<uint8**>(block);
        return block;
    }

    void PoolAllocator::free(uint8* data)
    {
        // Add the newly freed block to the front of the list
        *reinterpret_cast<uint8**>(data) = _freeHead;
        _freeHead = data;
    }
}
