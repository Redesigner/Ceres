#pragma once

#include "IVertexType.h"

#include "../../Common/Vector3.h"
#include "../../Common/Vector2.h"
#include "VertexPositionNormalTextureLayout.h"


namespace Ceres
{
    struct VertexPositionNormalTexture : public IVertexType
    {
        public:
            VertexPositionNormalTexture(Vector3 vertex, Vector3 normal, Vector2 texCoords) : Vertex(vertex), Normal(normal), TexCoords(texCoords) {};
            VertexPositionNormalTexture() : Vertex(Vector3(0)), Normal(Vector3::Zero()), TexCoords(Vector2(0.0f, 0.0f)) {};
            ~VertexPositionNormalTexture() {};

            Vector3 Vertex;
            Vector3 Normal;
            Vector2 TexCoords;

            using Layout = VertexPositionNormalTextureLayout;
    };
}