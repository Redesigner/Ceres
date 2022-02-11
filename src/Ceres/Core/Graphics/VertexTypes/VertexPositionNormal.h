#pragma once

#include "IVertexType.h"

#include "../../Common/Vector3.h"

namespace Ceres
{
    struct VertexPositionNormal : public IVertexType
    {
        public:
            VertexPositionNormal(Vector3 vertex, Vector3 normal) : Vertex(vertex), Normal(normal) {};
            VertexPositionNormal() : Vertex(Vector3(0)), Normal(Vector3::Zero()) {};
            ~VertexPositionNormal() {};

            Vector3 Vertex;
            Vector3 Normal;
    };
}