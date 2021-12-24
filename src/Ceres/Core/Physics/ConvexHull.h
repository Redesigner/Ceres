#pragma once

#include "IPrimitive.h"

namespace Ceres
{
    struct ConvexHull : public IPrimitive
    {
        ConvexHull(std::vector<Vector3>(vertices));

        virtual Vector3 FurthestVertex(Vector3 directionUnit) override;

        private:
            std::vector<Vector3> Vertices;
    };
}