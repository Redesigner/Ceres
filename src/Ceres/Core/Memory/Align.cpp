#include "Align.h"

#include <cassert>

#include "Ceres/Core/Math/Bitwise.h"

namespace Ceres
{
    uint8* alignPointer(uint8* data, SizeType alignment)
    {
        SizeType offset = alignment - (reinterpret_cast<SizeType>(data) % alignment);
        uint8* alignedPointer = (offset == alignment) ? data : data + offset;
        return alignedPointer;
    }

    uint8* allocAligned(SizeType size, SizeType alignment)
    {
        assert(isPowerOfTwo(alignment));

        // Allocate at least enough extra memory for realignment and storing the
        // original address
        SizeType allocSize = size + alignment + sizeof(SizeType) - 1;
        uint8* data = new uint8[allocSize];

        uint8* alignedData = alignPointer(data, alignment);
        SizeType offset = static_cast<SizeType>(alignedData - data);

        // Make sure we have enough memory to store the original unaligned address. Since
        // we're already aligned we need to increment the address by the alignment until
        // we have enough memory to store an address
        if (offset < sizeof(uint8*))
        {
            while (offset < sizeof(uint8*))
            {
                offset += alignment;
                alignedData += alignment;
            }
        }

        // Store the original address at the start of the block
        reinterpret_cast<uint8**>(alignedData)[-1] = data;

        return alignedData;
    }

    void freeAligned(uint8* data)
    {
        // Retrieve the original unaligned pointer stashed at the start of the block
        uint8* unalignedPointer = reinterpret_cast<uint8**>(data)[-1];
        delete[] unalignedPointer;
    }
}
