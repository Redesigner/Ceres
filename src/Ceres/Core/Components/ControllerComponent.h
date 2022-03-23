#pragma once

#include "Base/IComponent.h"

#include "../Input/InputHandler.h"

namespace Ceres
{
    class ControllerComponent : public IComponent
    {
        public:
            ControllerComponent(InputHandler& inputHandler);
            ~ControllerComponent();

            void Update(double seconds);

        private:
            const InputHandler& _inputHandler;
            float _rotation = 0.0f;
            float _ownerRotation = 0.0f;
            bool _canJump = false;
    };
}