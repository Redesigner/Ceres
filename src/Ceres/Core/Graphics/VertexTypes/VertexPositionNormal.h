#pragma once

#include "../../Common/Vector3.h"
#include "../VertexCollection.h"

namespace Ceres
{
    struct VertexNormal
    {
        public:
            VertexNormal(Vector3 vertex, Vector3 normal);
            ~VertexNormal();

            void SetAttributes();

            Vector3 Vertex;
            Vector3 Normal;
    };
}