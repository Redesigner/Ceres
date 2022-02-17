#pragma once

#include "IVertexLayout.h"

namespace Ceres
{
    class VertexPositionNormalTextureLayout : public IVertexLayout
    {
        public:
            virtual void SetAttributes() const override;
            virtual int Size() const override;

            static VertexPositionNormalTextureLayout& Get();
    };
}