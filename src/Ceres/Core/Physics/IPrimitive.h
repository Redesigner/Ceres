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
            virtual Vector3 FurthestVertex(Vector3 directionUnit) = 0;
            
            Transform Transform;
    };
}