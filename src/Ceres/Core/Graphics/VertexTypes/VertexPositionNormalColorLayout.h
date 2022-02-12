#pragma once

#include "IVertexLayout.h"

namespace Ceres
{
    class VertexPositionNormalColorLayout : public IVertexLayout
    {
        public:
            virtual void SetAttributes() const override;
            virtual int Size() const override;

            static VertexPositionNormalColorLayout& Get();
    };
}