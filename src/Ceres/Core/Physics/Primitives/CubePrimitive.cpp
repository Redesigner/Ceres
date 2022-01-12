#include "CubePrimitive.h"

namespace Ceres
{
    CubePrimitive::CubePrimitive(float size)
        :ConvexHull(VertexList(8))
    {
        _vertices[0] = Vector3(size / 2, size / 2, size / 2);
        _vertices[1] = Vector3(-size / 2, size / 2, size / 2);
        _vertices[2] = Vector3(size / 2, -size / 2, size / 2);
        _vertices[3] = Vector3(-size / 2, -size / 2, size / 2);
        _vertices[4] = Vector3(size / 2, size / 2, -size / 2);
        _vertices[5] = Vector3(-size / 2, size / 2, -size / 2);
        _vertices[6] = Vector3(size / 2, -size / 2, -size / 2);
        _vertices[7] = Vector3(-size / 2, -size / 2, -size / 2);
    }

    CubePrimitive::~CubePrimitive()
    {
        
    }
}