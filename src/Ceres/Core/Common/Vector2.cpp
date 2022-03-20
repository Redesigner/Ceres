#include "Vector2.h"

#include <cmath>

namespace Ceres
{
    Vector2::Vector2(float x, float y)
        :X(x), Y(y)
    {}

    Vector2::Vector2()
        :Vector2(0.0f, 0.0f)
    {}

    Vector2::~Vector2()
    {}

    float Vector2::LengthSquared() const
    {
        return X * X + Y * Y;
    }

    float Vector2::Length() const
    {
        return std::sqrtf(LengthSquared());
    }

    Vector2 Vector2::Normalize() const
    {
        const float lengthSquared = LengthSquared();
        if(lengthSquared == 0.0f)
        {
            return Vector2(0.0f, 0.0f);
        }
        const float length = std::sqrtf(lengthSquared);
        return Vector2(X / length, Y / length);
    }

    float Vector2::Dot(const Vector2& vector) const
    {
        return (X * vector.X) + (Y * vector.Y);
    }

    double Vector2::Angle(const Vector2& vector) const
    {
        const Vector2 a = Normalize();
        const Vector2 b = vector.Normalize();
        const float dot = a.Dot(b);
        if ((a.X == 0.0f && a.Y == 0.0f) || (b.X == 0.0f && b.Y == 0.0f))
        {
            return 0.0f;
        }
        return std::acos(dot);
    }

    bool Vector2::operator==(const Vector2& b) const
    {
        return X == b.X && Y == b.Y;
    }

    bool Vector2::operator!=(const Vector2& b) const
    {
        return X != b.X || Y != b.Y;
    }
}