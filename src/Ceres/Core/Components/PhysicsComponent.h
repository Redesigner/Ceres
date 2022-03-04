#pragma once

#include "Base/IComponent.h"
#include "../Physics/IPrimitive.h"
#include "../Physics/SweepResult.h"

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
            float SemiMajorAxis() const;
            IPrimitive*& GetPrimitive();
            void OnHit(SweepResult& sweepResult);

            Vector3 Velocity;
            Vector3 Acceleration;

            bool Paused = true;

        private:
            IPrimitive* _primitive;
    };
}