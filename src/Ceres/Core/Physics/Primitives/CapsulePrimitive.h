#pragma once

#include "../ConvexHull.h"

namespace Ceres
{
    struct CapsulePrimitive : public ConvexHull
    {
        public:
			CapsulePrimitive(float radius, float halfHeight);
        	~CapsulePrimitive();
            virtual float SemiMajorAxis() override;

            virtual float GetSphereRadius() const override;

        private:
            float _radius;
			float _halfHeight;
    };
}