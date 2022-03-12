#pragma once

#include "IVertexType.h"

#include "../../Common/Vector2.h"

namespace Ceres
{
    struct VertexPositionTexture : public IVertexType
    {
        public:
            VertexPositionTexture(Vector2 vertex, Vector2 uv) : Vertex(vertex), UV(uv) {};
            VertexPositionTexture() : Vertex(Vector2(0, 0)), UV(Vector2(0, 0)) {};
            ~VertexPositionTexture() {};

            Vector2 Vertex;
            Vector2 UV;
    };
}