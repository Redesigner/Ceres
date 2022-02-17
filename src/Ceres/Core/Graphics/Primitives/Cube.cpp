#include "Cube.h"

namespace Ceres
{
    template <typename T>
    Cube<T>::Cube(float x, float y, float z)
        : MeshPrimitive<T>(24,36)
    {}

    template <typename T>
    Cube<T>::~Cube()
    {}

    Cube<VertexPositionNormalColor>::Cube(float x, float y, float z, Color color)
        : MeshPrimitive<VertexPositionNormalColor>(24, 36) 
    {
        using Vertex = VertexPositionNormalColor;
        // Bottom
        _typedVertices[0] = Vertex(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 0, -1), color);
        _typedVertices[1] = Vertex(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 0, -1), color);
        _typedVertices[2] = Vertex(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, 0, -1), color);
        _typedVertices[3] = Vertex(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, 0, -1), color);
        // Top
        _typedVertices[4] = Vertex(Vector3(x / 2, y / 2, z / 2), Vector3(0, 0, 1), color);
        _typedVertices[5] = Vertex(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 0, 1), color);
        _typedVertices[6] = Vertex(Vector3(x / 2, -y / 2, z / 2), Vector3(0, 0, 1), color);
        _typedVertices[7] = Vertex(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, 0, 1), color);
        // Back
        _typedVertices[8] = Vertex(Vector3(x / 2, y / 2, z / 2), Vector3(1, 0, 0), color);
        _typedVertices[9] = Vertex(Vector3(x / 2, y / 2, -z / 2), Vector3(1, 0, 0), color);
        _typedVertices[10] = Vertex(Vector3(x / 2, -y / 2, z / 2), Vector3(1, 0, 0), color);
        _typedVertices[11] = Vertex(Vector3(x / 2, -y / 2, -z / 2), Vector3(1, 0, 0), color);
        // Front
        _typedVertices[12] = Vertex(Vector3(-x / 2, y / 2, z / 2), Vector3(-1, 0, 0), color);
        _typedVertices[13] = Vertex(Vector3(-x / 2, y / 2, -z / 2), Vector3(-1, 0, 0), color);
        _typedVertices[14] = Vertex(Vector3(-x / 2, -y / 2, z / 2), Vector3(-1, 0, 0), color);
        _typedVertices[15] = Vertex(Vector3(-x / 2, -y / 2, -z / 2), Vector3(-1, 0, 0), color);
        // Left
        _typedVertices[16] = Vertex(Vector3(x / 2, y / 2, z / 2), Vector3(0, 1, 0), color);
        _typedVertices[17] = Vertex(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 1, 0), color);
        _typedVertices[18] = Vertex(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 1, 0), color);
        _typedVertices[19] = Vertex(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 1, 0), color);
        // Right
        _typedVertices[20] = Vertex(Vector3(x / 2, -y / 2, z / 2), Vector3(0, -1, 0), color);
        _typedVertices[21] = Vertex(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, -1, 0), color);
        _typedVertices[22] = Vertex(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, -1, 0), color);
        _typedVertices[23] = Vertex(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, -1, 0), color);
        _indices = new uint[36]{
            0, 1, 2, 1, 3, 2,
            4, 5, 6, 5, 7, 6,
            10, 11, 9, 10, 9, 8,
            12, 13, 14, 13, 15, 14,
            16, 17, 18, 17, 19, 18,
            22, 23, 21, 22, 21, 20
        };
    }

    Cube<VertexPositionNormalTexture>::Cube(float x, float y, float z)
        : MeshPrimitive<VertexPositionNormalTexture>(24, 36)
    {
        using Vertex = VertexPositionNormalTexture;
        // Bottom
        _typedVertices[0] = Vertex(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 0, -1), Vector2(0, 1));
        _typedVertices[1] = Vertex(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 0, -1), Vector2(0, 0));
        _typedVertices[2] = Vertex(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, 0, -1), Vector2(1, 1));
        _typedVertices[3] = Vertex(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, 0, -1), Vector2(1, 0));
        // Top
        _typedVertices[4] = Vertex(Vector3(x / 2, y / 2, z / 2), Vector3(0, 0, 1), Vector2(0, 1));
        _typedVertices[5] = Vertex(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 0, 1), Vector2(0, 0));
        _typedVertices[6] = Vertex(Vector3(x / 2, -y / 2, z / 2), Vector3(0, 0, 1), Vector2(1, 1));
        _typedVertices[7] = Vertex(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, 0, 1), Vector2(1, 0));
        // Back
        _typedVertices[8] = Vertex(Vector3(x / 2, y / 2, z / 2), Vector3(1, 0, 0), Vector2(1, 1));
        _typedVertices[9] = Vertex(Vector3(x / 2, y / 2, -z / 2), Vector3(1, 0, 0), Vector2(1, 0));
        _typedVertices[10] = Vertex(Vector3(x / 2, -y / 2, z / 2), Vector3(1, 0, 0), Vector2(0, 1));
        _typedVertices[11] = Vertex(Vector3(x / 2, -y / 2, -z / 2), Vector3(1, 0, 0), Vector2(0, 0));
        // Front
        _typedVertices[12] = Vertex(Vector3(-x / 2, y / 2, z / 2), Vector3(-1, 0, 0), Vector2(0, 1));
        _typedVertices[13] = Vertex(Vector3(-x / 2, y / 2, -z / 2), Vector3(-1, 0, 0), Vector2(0, 0));
        _typedVertices[14] = Vertex(Vector3(-x / 2, -y / 2, z / 2), Vector3(-1, 0, 0), Vector2(1, 1));
        _typedVertices[15] = Vertex(Vector3(-x / 2, -y / 2, -z / 2), Vector3(-1, 0, 0), Vector2(1, 0));
        // Left
        _typedVertices[16] = Vertex(Vector3(x / 2, y / 2, z / 2), Vector3(0, 1, 0), Vector2(0, 1));
        _typedVertices[17] = Vertex(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 1, 0), Vector2(0, 0));
        _typedVertices[18] = Vertex(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 1, 0), Vector2(1, 1));
        _typedVertices[19] = Vertex(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 1, 0), Vector2(1, 0));
        // Right
        _typedVertices[20] = Vertex(Vector3(x / 2, -y / 2, z / 2), Vector3(0, -1, 0), Vector2(1, 1));
        _typedVertices[21] = Vertex(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, -1, 0), Vector2(1, 0));
        _typedVertices[22] = Vertex(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, -1, 0), Vector2(0, 1));
        _typedVertices[23] = Vertex(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, -1, 0), Vector2(0, 0));
        _indices = new uint[36]{
            0, 1, 2, 1, 3, 2,
            4, 5, 6, 5, 7, 6,
            10, 11, 9, 10, 9, 8,
            12, 13, 14, 13, 15, 14,
            16, 17, 18, 17, 19, 18,
            22, 23, 21, 22, 21, 20
        };
    }
}