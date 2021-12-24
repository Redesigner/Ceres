#pragma once

#include "Buttons.h"

namespace Ceres
{
    struct Axis
    {
        public:
            Axis(Button positive, Button negative);
            ~Axis();
            
            Button Positive, Negative;
    };
}