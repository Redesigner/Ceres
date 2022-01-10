#pragma once

#include "../Common/Vector3.h"
#include "../Common/Transform.h"

#include <vector>

namespace Ceres
{
    struct IPrimitive
    {
        IPrimitive();
        ~IPrimitive();

        public:
            virtual std::vector<Vector3> FurthestVertex(Vector3 directionUnit) = 0;
            virtual float SemiMajorAxis() = 0;

            virtual Transform GetTransform();
            virtual void SetTransform(Transform transform);

        private:
            Transform _transform;
    };
}