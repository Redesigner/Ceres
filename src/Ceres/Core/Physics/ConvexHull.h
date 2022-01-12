#pragma once

#include "IPrimitive.h"
#include "../Common/VertexList.h"

namespace Ceres
{
    struct ConvexHull : public IPrimitive
    {
        ConvexHull(VertexList(vertices));

        virtual VertexList FurthestVertex(Vector3 directionUnit) override;
        virtual float SemiMajorAxis() override;
        virtual void SetTransform(Transform transform) override;

        VertexList _vertices;

        private:
            bool nearlyEqual(float a, float b);

            bool _semiMajorAxisCached = false;
            float _semiMajorAxis;
    };
}