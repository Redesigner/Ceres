#pragma once

#include "../VertexTypes/VertexPositionNormalColor.h"
#include "../VertexTypes/VertexPositionNormalColorLayout.h"
#include "../VertexTypes/IVertexLayout.h"

namespace Ceres
{
    struct Cube
    {
        public:
            Cube(float x, float y, float z, Color color);
            ~Cube();

            const VertexPositionNormalColor Vertices[24];
            const int Indices[36];
    };
}