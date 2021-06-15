#pragma once

#include "../VertexTypes/VertexPositionNormal.h"
#include "../VertexTypes/VertexPositionNormalLayout.h"
#include "../VertexTypes/IVertexLayout.h"

namespace Ceres
{
    struct Cube
    {
        public:
            Cube(float x, float y, float z);
            ~Cube();

            const VertexPositionNormal Vertices[24];
            const int Indices[36];
    };
}