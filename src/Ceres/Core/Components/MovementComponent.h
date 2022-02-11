#pragma once

#include "Base/IComponent.h"

namespace Ceres
{
    class MovementComponent : public IComponent
    {
        public:
            MovementComponent(const IEntity& parent);
            ~MovementComponent();

            virtual bool RecieveMessage(Message* message) override;

        private:
    };
}