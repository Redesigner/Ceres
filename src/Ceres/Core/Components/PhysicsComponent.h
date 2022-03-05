#pragma once

#include "Base/IComponent.h"
#include "../Physics/IPrimitive.h"
#include "../Physics/SweepResult.h"

#include <memory>

namespace Ceres
{
    class PhysicsComponent : public IComponent
    {
        using PrimitivePtr = std::shared_ptr<IPrimitive>;
        public:
            PhysicsComponent(PrimitivePtr &primitive);
            ~PhysicsComponent();

            virtual bool RecieveMessage(Message& message) override;

            const Vector3 GetPosition() const;
            void SetPosition(Vector3 newPosition);
            float SemiMajorAxis() const;
            PrimitivePtr& GetPrimitive();
            void OnHit(SweepResult& sweepResult);

            Vector3 Velocity;
            Vector3 Acceleration;

            bool Paused = true;

        private:
            PrimitivePtr _primitive;
    };
}