#pragma once

#include "IVertexType.h"
#include "../../Common/Vector3.h"

namespace Ceres
{
    struct VertexPosition : IVertexType
    {
        public:
            VertexPosition(Vector3 position);
            ~VertexPosition();

            static void SetAttributes();

            Vector3 Position;
    };
}