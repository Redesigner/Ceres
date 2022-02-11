#include "Cube.h"

namespace Ceres
{
    Cube::Cube(float x, float y, float z, Color color)
        :Vertices{
            // Front
            VertexPositionNormalColor(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 0, -1), color),
            VertexPositionNormalColor(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 0, -1), color),
            VertexPositionNormalColor(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, 0, -1), color),
            VertexPositionNormalColor(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, 0, -1), color),
            // Back
            VertexPositionNormalColor(Vector3(x / 2, y / 2, z / 2), Vector3(0, 0, 1), color),
            VertexPositionNormalColor(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 0, 1), color),
            VertexPositionNormalColor(Vector3(x / 2, -y / 2, z / 2), Vector3(0, 0, 1), color),
            VertexPositionNormalColor(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, 0, 1), color),
            // Right
            VertexPositionNormalColor(Vector3(x / 2, y / 2, z / 2), Vector3(1, 0, 0), color),
            VertexPositionNormalColor(Vector3(x / 2, y / 2, -z / 2), Vector3(1, 0, 0), color),
            VertexPositionNormalColor(Vector3(x / 2, -y / 2, z / 2), Vector3(1, 0, 0), color),
            VertexPositionNormalColor(Vector3(x / 2, -y / 2, -z / 2), Vector3(1, 0, 0), color),
            // Left
            VertexPositionNormalColor(Vector3(-x / 2, y / 2, z / 2), Vector3(-1, 0, 0), color),
            VertexPositionNormalColor(Vector3(-x / 2, y / 2, -z / 2), Vector3(-1, 0, 0), color),
            VertexPositionNormalColor(Vector3(-x / 2, -y / 2, z / 2), Vector3(-1, 0, 0), color),
            VertexPositionNormalColor(Vector3(-x / 2, -y / 2, -z / 2), Vector3(-1, 0, 0), color),
            // Top
            VertexPositionNormalColor(Vector3(x / 2, y / 2, z / 2), Vector3(0, 1, 0), color),
            VertexPositionNormalColor(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 1, 0), color),
            VertexPositionNormalColor(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 1, 0), color),
            VertexPositionNormalColor(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 1, 0), color),
            // Bottom
            VertexPositionNormalColor(Vector3(x / 2, -y / 2, z / 2), Vector3(0, -1, 0), color),
            VertexPositionNormalColor(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, -1, 0), color),
            VertexPositionNormalColor(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, -1, 0), color),
            VertexPositionNormalColor(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, -1, 0), color)
        },
        Indices
        {
            0, 1, 2, 1, 3, 2,
            4, 5, 6, 5, 7, 6,
            10, 11, 9, 10, 9, 8,
            12, 13, 14, 13, 15, 14,
            16, 17, 18, 17, 19, 18,
            22, 23, 21, 22, 21, 20
        }    
    {      
    }

    Cube::~Cube()
    {}
}