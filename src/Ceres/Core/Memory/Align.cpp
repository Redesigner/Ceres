#include "Align.h"

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
        // Allocate at least enough extra memory for realignment and
        // storing the original address
        SizeType allocSize = size + alignment + sizeof(SizeType) - 1;
        uint8* data = new uint8[allocSize];

        uint8* alignedData = alignPointer(data, alignment);
        SizeType offset = static_cast<uint8>(alignedData - data);

        // Make sure we have enough memory to store the original
        // unaligned address. Since we're already aligned we need to
        // increment the address by the alignment
        if (offset < sizeof(SizeType))
        {
            offset += alignment;
            alignedData += alignment;
        }

        // Store the original address at the start of the block
        reinterpret_cast<SizeType*>(alignedData)[-1] = reinterpret_cast<SizeType>(data);

        return alignedData;
    }

    void freeAligned(uint8* data)
    {
        uint8* unalignedPointer = reinterpret_cast<uint8*>(reinterpret_cast<SizeType*>(data)[-1]);
        delete[] unalignedPointer;
    }
}
