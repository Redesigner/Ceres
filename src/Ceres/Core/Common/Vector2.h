#pragma once

#include "Vector3.h"

namespace Ceres
{
    /**
     * @brief 2-dimensional vector
     * 
     */
    struct Vector2
    {
        Vector2(float x, float y);
        Vector2();
        ~Vector2();

        float LengthSquared() const;
        float Length() const;
        Vector2 Normalize() const;
        float Dot(const Vector2& vector) const;
        double Angle(const Vector2& vector) const;

        explicit operator Vector3() const { return Vector3(X, Y, 0.0f); }

        bool operator==(const Vector2& b) const;
        bool operator!=(const Vector2& b) const;

        float X;
        float Y;
    };
}