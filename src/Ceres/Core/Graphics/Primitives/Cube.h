#pragma once

#include "MeshPrimitive.h"

#include "../VertexTypes/VertexPositionNormalColor.h"
#include "../VertexTypes/VertexPositionNormalTexture.h"

#include "../VertexTypes/VertexPositionNormalColorLayout.h"

namespace Ceres
{
    template <typename T>
    struct Cube : public MeshPrimitive<T>
    {
        public:
            Cube(float x, float y, float z);
            ~Cube();
    };
    template <>
    struct Cube<VertexPositionNormalColor> : public MeshPrimitive<VertexPositionNormalColor>
    {
        public:
            Cube(float x, float y, float z, Color color);
    };

    template <>
    struct Cube<VertexPositionNormalTexture> : public MeshPrimitive<VertexPositionNormalTexture>
    {
        public:
            Cube(float x, float y, float z);
    };
}