#pragma once

#include "IVertexLayout.h"

namespace Ceres
{
    class VertexPositionNormalColorLayout : public IVertexLayout
    {
        public:
            void SetAttributes() const override;
            int Size() const override;
    };
}