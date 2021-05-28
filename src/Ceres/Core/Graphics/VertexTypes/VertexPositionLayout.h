#pragma once

#include "IVertexLayout.h"

namespace Ceres
{
    class VertexPositionLayout : public IVertexLayout
    {
        public:
            virtual void SetAttributes() const override;
            virtual int Size() const override;
    };
}