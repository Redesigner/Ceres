#pragma once

#include "MeshPrimitive.h"

#include "../VertexTypes/VertexPositionNormalColor.h"
#include "../VertexTypes/VertexPositionNormalColorLayout.h"

namespace Ceres
{
    struct Cube : public MeshPrimitive<VertexPositionNormalColor>
    {
        public:
            Cube(float x, float y, float z, Color color);
            ~Cube();
    };
}