#pragma once

#include "IVertexType.h"

#include "../../Common/Vector3.h"
#include "../../Common/Color.h"

namespace Ceres
{
    struct VertexPositionNormalColor : public IVertexType
    {
        public:
            VertexPositionNormalColor(Vector3 vertex, Vector3 normal, Color color) : Vertex(vertex), Normal(normal), Color(color) {};
            VertexPositionNormalColor() : Vertex(Vector3(0)), Normal(Vector3::Zero()), Color(0, 0, 0) {};
            ~VertexPositionNormalColor() {};

            Vector3 Vertex;
            Vector3 Normal;
            Color Color;
    };
}