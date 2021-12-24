#pragma once

#include "Buttons.h"
#include "../Common/Vector2.h"

namespace Ceres
{
    struct Axis2D
    {
        public:
            Axis2D(Button up, Button down, Button left, Button right);
            ~Axis2D();
            
            Button Up, Left, Down, Right;
    };
}