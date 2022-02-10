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

            virtual float GetSphereRadius() const override;

        private:
            float _radius;
    };
}