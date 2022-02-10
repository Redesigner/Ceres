#pragma once

#include "../IPrimitive.h"

namespace Ceres
{
    struct SpherePrimitive : public IPrimitive
    {
        SpherePrimitive(float radius);
        ~SpherePrimitive();

        public:
            virtual VertexList FurthestVertex(Vector3 directionUnit) override;
            virtual float SemiMajorAxis() override;

        private:
            float _radius;
    };
}