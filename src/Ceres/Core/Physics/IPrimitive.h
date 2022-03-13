#pragma once

#include "../Common/Vector3.h"
#include "../Common/VertexList.h"
#include "../Common/Transform.h"

#include <vector>

namespace Ceres
{
    /**
     * @brief Mathematical representation of a 3D shape, for use in collision detection
     * 
     */
    struct IPrimitive
    {
        IPrimitive();
        ~IPrimitive();

        public:
            virtual VertexList FurthestVertex(Vector3 directionUnit) = 0;

            /**
             * @brief Get the longest semi-major axis of a shape, i.e., the longest possible line from the center of the shape to a point on its surface. Used for a broad-phase collision detection
             * 
             * @return float 
             */
            virtual float SemiMajorAxis() = 0;

            /// The collision algorithm doesn't play nice with rounded edges, so spheres are handled after the initial collision detection
            /// this should be overriden for any non-polygonal shapes. Otherwise, it should always return 0.

            /**
             * @brief Get the radius of our shape's spherical component. For a polygon, this is 0. For a sphere, this is the sphere's radius
             * 
             * @return float 
             */
            virtual float GetSphereRadius() const;
            virtual Transform GetTransform() const;
            virtual void SetTransform(Transform transform);

        private:
            Transform _transform;
    };
}