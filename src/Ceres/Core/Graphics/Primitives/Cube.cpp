#include "Cube.h"

namespace Ceres
{
    Cube::Cube(float x, float y, float z)
        :Vertices{
            // Front
            VertexPositionNormal(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 0, -1)),
            VertexPositionNormal(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 0, -1)),
            VertexPositionNormal(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, 0, -1)),
            VertexPositionNormal(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, 0, -1)),
            // Back
            VertexPositionNormal(Vector3(x / 2, y / 2, z / 2), Vector3(0, 0, 1)),
            VertexPositionNormal(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 0, 1)),
            VertexPositionNormal(Vector3(x / 2, -y / 2, z / 2), Vector3(0, 0, 1)),
            VertexPositionNormal(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, 0, 1)),
            // Right
            VertexPositionNormal(Vector3(x / 2, y / 2, z / 2), Vector3(1, 0, 0)),
            VertexPositionNormal(Vector3(x / 2, y / 2, -z / 2), Vector3(1, 0, 0)),
            VertexPositionNormal(Vector3(x / 2, -y / 2, z / 2), Vector3(1, 0, 0)),
            VertexPositionNormal(Vector3(x / 2, -y / 2, -z / 2), Vector3(1, 0, 0)),
            // Left
            VertexPositionNormal(Vector3(-x / 2, y / 2, z / 2), Vector3(-1, 0, 0)),
            VertexPositionNormal(Vector3(-x / 2, y / 2, -z / 2), Vector3(-1, 0, 0)),
            VertexPositionNormal(Vector3(-x / 2, -y / 2, z / 2), Vector3(-1, 0, 0)),
            VertexPositionNormal(Vector3(-x / 2, -y / 2, -z / 2), Vector3(-1, 0, 0)),
            // Top
            VertexPositionNormal(Vector3(x / 2, y / 2, z / 2), Vector3(0, 1, 0)),
            VertexPositionNormal(Vector3(x / 2, y / 2, -z / 2), Vector3(0, 1, 0)),
            VertexPositionNormal(Vector3(-x / 2, y / 2, z / 2), Vector3(0, 1, 0)),
            VertexPositionNormal(Vector3(-x / 2, y / 2, -z / 2), Vector3(0, 1, 0)),
            // Bottom
            VertexPositionNormal(Vector3(x / 2, -y / 2, z / 2), Vector3(0, -1, 0)),
            VertexPositionNormal(Vector3(x / 2, -y / 2, -z / 2), Vector3(0, -1, 0)),
            VertexPositionNormal(Vector3(-x / 2, -y / 2, z / 2), Vector3(0, -1, 0)),
            VertexPositionNormal(Vector3(-x / 2, -y / 2, -z / 2), Vector3(0, -1, 0))
        },
        Indices
        {
            0, 1, 2, 1, 2, 3,
            4, 5, 6, 5, 6, 7,
            8, 9, 10, 9, 10, 11,
            12, 13, 14, 13, 14, 15,
            16, 17, 18, 17, 18, 19,
            20, 21, 22, 21, 22, 23
        }    
    {      
    }

    Cube::~Cube()
    {}
}