#pragma once

#include <cstdint>

#if defined(__LP64__) || defined(_WIN64)
    #define CERES_TARGET_64
#else
    #define CERES_TARGET_32
#endif

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

namespace Ceres
{
    #if defined(CERES_TARGET_64)
        using SizeType = uint64;
    #else
        using SizeType = uint32;
    #endif
}
