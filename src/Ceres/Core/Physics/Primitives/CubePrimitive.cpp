#include "CubePrimitive.h"

namespace Ceres
{
    CubePrimitive::CubePrimitive(float size)
        :ConvexHull({
            Vector3(size / 2, size / 2, size / 2),
            Vector3(-size / 2, size / 2, size / 2),
            Vector3(size / 2, -size / 2, size / 2),
            Vector3(-size / 2, -size / 2, size / 2),
            Vector3(size / 2, size / 2, -size / 2),
            Vector3(-size / 2, size / 2, -size / 2),
            Vector3(size / 2, -size / 2, -size / 2),
            Vector3(-size / 2, -size / 2, -size / 2)
        })
    {}

    CubePrimitive::~CubePrimitive()
    {
        
    }
}