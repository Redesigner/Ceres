#pragma once

#include <type_traits>

namespace Ceres
{
    template<typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    bool isPowerOfTwo(T integer)
    {
        return (integer != 0) && ((integer & (integer - 1)) == 0);
    }
}
