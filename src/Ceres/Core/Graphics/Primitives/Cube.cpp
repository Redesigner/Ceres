#include "Cube.h"

namespace Ceres
{
    Cube::Cube(float x, float y, float z, Color color)
        : MeshPrimitive<VertexPositionNormalColor>(24, 36) 
    {
        // Front
        _typedVertices[0] = VertexPositionNormalColor(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 0, -1), color);
        _typedVertices[1] = VertexPositionNormalColor(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 0, -1), color);
        _typedVertices[2] = VertexPositionNormalColor(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, 0, -1), color);
        _typedVertices[3] = VertexPositionNormalColor(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, 0, -1), color);
        // Back
        _typedVertices[4] = VertexPositionNormalColor(Vector3(x / 2, y / 2, z / 2), Vector3(0, 0, 1), color);
        _typedVertices[5] = VertexPositionNormalColor(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 0, 1), color);
        _typedVertices[6] = VertexPositionNormalColor(Vector3(x / 2, -y / 2, z / 2), Vector3(0, 0, 1), color);
        _typedVertices[7] = VertexPositionNormalColor(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, 0, 1), color);
        // Right
        _typedVertices[8] = VertexPositionNormalColor(Vector3(x / 2, y / 2, z / 2), Vector3(1, 0, 0), color);
        _typedVertices[9] = VertexPositionNormalColor(Vector3(x / 2, y / 2, -z / 2), Vector3(1, 0, 0), color);
        _typedVertices[10] = VertexPositionNormalColor(Vector3(x / 2, -y / 2, z / 2), Vector3(1, 0, 0), color);
        _typedVertices[11] = VertexPositionNormalColor(Vector3(x / 2, -y / 2, -z / 2), Vector3(1, 0, 0), color);
        // Left
        _typedVertices[12] = VertexPositionNormalColor(Vector3(-x / 2, y / 2, z / 2), Vector3(-1, 0, 0), color);
        _typedVertices[13] = VertexPositionNormalColor(Vector3(-x / 2, y / 2, -z / 2), Vector3(-1, 0, 0), color);
        _typedVertices[14] = VertexPositionNormalColor(Vector3(-x / 2, -y / 2, z / 2), Vector3(-1, 0, 0), color);
        _typedVertices[15] = VertexPositionNormalColor(Vector3(-x / 2, -y / 2, -z / 2), Vector3(-1, 0, 0), color);
        // Top
        _typedVertices[16] = VertexPositionNormalColor(Vector3(x / 2, y / 2, z / 2), Vector3(0, 1, 0), color);
        _typedVertices[17] = VertexPositionNormalColor(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 1, 0), color);
        _typedVertices[18] = VertexPositionNormalColor(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 1, 0), color);
        _typedVertices[19] = VertexPositionNormalColor(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 1, 0), color);
        // Bottom
        _typedVertices[20] = VertexPositionNormalColor(Vector3(x / 2, -y / 2, z / 2), Vector3(0, -1, 0), color);
        _typedVertices[21] = VertexPositionNormalColor(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, -1, 0), color);
        _typedVertices[22] = VertexPositionNormalColor(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, -1, 0), color);
        _typedVertices[23] = VertexPositionNormalColor(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, -1, 0), color);
        _indices = new uint[36]{
            0, 1, 2, 1, 3, 2,
            4, 5, 6, 5, 7, 6,
            10, 11, 9, 10, 9, 8,
            12, 13, 14, 13, 15, 14,
            16, 17, 18, 17, 19, 18,
            22, 23, 21, 22, 21, 20
        };
    }

    Cube::~Cube()
    {}
}