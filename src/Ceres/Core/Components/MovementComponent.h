#pragma once

#include "Base/IComponent.h"

namespace Ceres
{
    class MovementComponent : public IComponent
    {
        public:
            MovementComponent();
            ~MovementComponent();

            virtual bool ReceiveMessage(Message& message) override;

        private:
            bool _grounded = false;
    };
}