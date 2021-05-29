#pragma once

#include <Ceres/Core/Common/Types.h>

namespace Ceres
{
    uint8* alignPointer(uint8* pointer, SizeType size);
    uint8* allocAligned(SizeType size, SizeType alignment);
    void freeAligned(uint8* data);
}
