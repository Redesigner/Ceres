#pragma once

#include "Base/IComponent.h"

#include "../Input/InputHandler.h"

namespace Ceres
{
    class ControllerComponent : public IComponent
    {
        public:
            ControllerComponent(const IEntity& parent, InputHandler& inputHandler);
            ~ControllerComponent();

            virtual bool RecieveMessage(Message* message) override;
            void Update(double seconds);

        private:
            const InputHandler& _inputHandler;
            float _rotation = 0;
    };
}