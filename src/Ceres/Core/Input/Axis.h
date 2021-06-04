#pragma once

#include "Buttons.h"
#include "../Common/Vector2.h"

namespace Ceres
{
    struct Axis
    {
        public:
            Axis(Button up, Button down, Button left, Button right);
            ~Axis();
            
            Button Up, Left, Down, Right;
    };
}