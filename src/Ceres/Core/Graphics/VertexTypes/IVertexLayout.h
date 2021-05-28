#pragma once

namespace Ceres
{
    class IVertexLayout
    {
        public:
            virtual void SetAttributes() const = 0;
            virtual int Size() const = 0;
    };
}