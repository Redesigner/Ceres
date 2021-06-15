#pragma once

#include "IVertexLayout.h"

namespace Ceres
{
    class VertexPositionNormalLayout : public IVertexLayout
    {
        public:
            void SetAttributes() const;
            int Size() const;
    };
}