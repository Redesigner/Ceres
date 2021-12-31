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

            const Vector3 GetPosition() const;
            void SetPosition(Vector3 newPosition);

            Vector3 Velocity;

        private:
            IPrimitive* Primitive;
    };
}