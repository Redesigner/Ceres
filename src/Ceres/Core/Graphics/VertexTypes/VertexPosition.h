#pragma once

#include "IVertexType.h"

#include "../../Common/Vector3.h"

namespace Ceres
{
    struct VertexPosition : IVertexType
    {
        public:
            VertexPosition(Vector3 position) : Position(position) {};
            VertexPosition() : Position(Vector3::Zero()) {};
            ~VertexPosition() {};

            Vector3 Position;
    };
}