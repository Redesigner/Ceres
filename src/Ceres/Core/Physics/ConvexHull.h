#pragma once

#include "IPrimitive.h"

namespace Ceres
{
    struct ConvexHull : public IPrimitive
    {
        ConvexHull(std::vector<Vector3>(vertices));

        virtual std::vector<Vector3> FurthestVertex(Vector3 directionUnit) override;
        virtual float SemiMajorAxis() override;
        virtual void SetTransform(Transform transform) override;

        // should be private, access changed for debug
        std::vector<Vector3> _vertices;

        private:
            bool nearlyEqual(float a, float b);

            bool _semiMajorAxisCached = false;
            float _semiMajorAxis;
    };
}