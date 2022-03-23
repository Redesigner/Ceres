#include "PhysicsComponent.h"

#include "../Entities/Base/IEntity.h"
#include <fmt/core.h>

namespace Ceres
{
    using PrimitivePtr = std::shared_ptr<IPrimitive>;

    PhysicsComponent::PhysicsComponent(PrimitivePtr &primitive)
        :IComponent(std::type_index(typeid(PhysicsComponent))), _primitive(primitive)
    {
        addMessageHandler("Position", [](IComponent* component, Message& message)
            {
                PhysicsComponent* physics = static_cast<PhysicsComponent*>(component);
                Transform& newTransform = physics->_primitive->GetTransform();
                newTransform.SetPosition(message.GetData<Vector3>());
                physics->_primitive->SetTransform(newTransform);
            });

        addMessageHandler("Rotate", [](IComponent* component, Message& message)
            {
                PhysicsComponent* physics = static_cast<PhysicsComponent*>(component);
                Transform& newTransform = physics->_primitive->GetTransform();
                newTransform.SetRotation(newTransform.GetRotation() + message.GetData<Vector3>());
                physics->_primitive->SetTransform(newTransform);
            });

        addMessageHandler("Scale", [](IComponent* component, Message& message)
            {
                PhysicsComponent* physics = static_cast<PhysicsComponent*>(component);
                Transform& newTransfrom = physics->_primitive->GetTransform();
                newTransfrom.SetScale(message.GetData<Vector3>());
                physics->_primitive->SetTransform(newTransfrom);
            });

        addMessageHandler("Acceleration", [](IComponent* component, Message& message)
            {
                PhysicsComponent* physics = static_cast<PhysicsComponent*>(component);
                physics->Acceleration += message.GetData<Vector3>();
            });

        addMessageHandler("Pause", [](IComponent* component, Message& message)
            {
                PhysicsComponent* physics = static_cast<PhysicsComponent*>(component);
                physics->Paused = !physics->Paused;
            });
    }

    PhysicsComponent::~PhysicsComponent()
    {
    }

    const Vector3 PhysicsComponent::GetPosition() const
    {
        return _primitive->GetTransform().GetPosition();
    }

    void PhysicsComponent::SetPosition(Vector3 newPosition)
    {
        // TODO: Change the way we access the private transform?
        Transform newTransform = _primitive->GetTransform();
        newTransform.SetPosition(newPosition);
        _primitive->SetTransform(newTransform);
        sendMessage(Message::Write("Position", newPosition));
    }

    float PhysicsComponent::SemiMajorAxis() const
    {
        return _primitive->SemiMajorAxis();
    }

    PrimitivePtr& PhysicsComponent::GetPrimitive()
    {
        return _primitive;
    }

    void PhysicsComponent::OnHit(SweepResult& SweepResult)
    {
    }

    void PhysicsComponent::SetGrounded(const bool grounded)
    {
        if (!_grounded && grounded)
        {
            sendMessage(Message::Write("Landed", true));
        }
        else if (_grounded && !grounded)
        {
            sendMessage(Message::Write("Landed", false));
        }
        _grounded = grounded;
    }

    void PhysicsComponent::FinalizeVelocity()
    {
        sendMessage(Message::Write("Velocity", Velocity));
        std::string velocity = Velocity.ToString();
        sendMessage(Message::Write("Text", velocity));
    }
}