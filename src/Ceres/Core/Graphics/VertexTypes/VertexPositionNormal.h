#pragma once

#include "../../Common/Vector3.h"

namespace Ceres
{
    struct VertexPositionNormal
    {
        public:
            VertexPositionNormal(Vector3 vertex, Vector3 normal);
            ~VertexPositionNormal();

            Vector3 Vertex;
            Vector3 Normal;
    };
}