#pragma once

#include "Base/IComponent.h"
#include "../Physics/IPrimitive.h"

namespace Ceres
{
    class PhysicsComponent : public IComponent
    {
        public:
            PhysicsComponent(const IEntity& parent, IPrimitive* primitive);
            ~PhysicsComponent();

            virtual bool RecieveMessage(Message* message) override;

        private:
            IPrimitive* Primitive;
    };
}