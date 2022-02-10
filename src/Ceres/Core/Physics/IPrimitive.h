#pragma once

#include "../Common/Vector3.h"
#include "../Common/VertexList.h"
#include "../Common/Transform.h"

#include <vector>

namespace Ceres
{
    struct IPrimitive
    {
        IPrimitive();
        ~IPrimitive();

        public:
            virtual VertexList FurthestVertex(Vector3 directionUnit) = 0;
            virtual float SemiMajorAxis() = 0;

            /// The collision algorithm doesn't play nice with rounded edges, so spheres are handled after the initial collision detection
            /// this should be overriden for any non-polygonal shapes. Otherwise, it should always return 0.
            virtual float GetSphereRadius() const;
            virtual Transform GetTransform() const;
            virtual void SetTransform(Transform transform);

        private:
            Transform _transform;
    };
}