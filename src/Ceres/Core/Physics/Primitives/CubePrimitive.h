#pragma once


#include "../ConvexHull.h"

namespace Ceres
{
    struct CubePrimitive : public ConvexHull
    {
        CubePrimitive(float size);
        ~CubePrimitive();
    };
}