#pragma once

namespace Ceres
{
    struct Vector2
    {
        Vector2(float x, float y);
        ~Vector2();

        Vector2 Normalize();

        float X;
        float Y;
    };
}