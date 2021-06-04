#include "Vector2.h"

#include <cmath>

namespace Ceres
{
    Vector2::Vector2(float x, float y)
        :X(x), Y(y)
    {}

    Vector2::~Vector2()
    {}

    Vector2 Vector2::Normalize()
    {
        float length = std::sqrtf((X * X) + (Y * Y));
        if(length == 0)
        {
            return Vector2(0, 0);
        }
        return Vector2(X / length, Y / length);
    }
}