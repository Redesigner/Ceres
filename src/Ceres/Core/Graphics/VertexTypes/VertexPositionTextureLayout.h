#pragma once

#include "IVertexLayout.h"

namespace Ceres
{
    class VertexPositionTextureLayout : public IVertexLayout
    {
        public:
            void SetAttributes() const;
            int Size() const;

            static VertexPositionTextureLayout& Get();
    };
}