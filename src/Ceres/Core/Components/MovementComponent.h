#pragma once

#include "Base/IComponent.h"

namespace Ceres
{
    class MovementComponent : public IComponent
    {
        public:
            MovementComponent();
            ~MovementComponent();

        private:
            bool _grounded = false;
    };
}