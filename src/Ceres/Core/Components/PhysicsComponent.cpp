#include "PhysicsComponent.h"

#include "../Entities/Base/IEntity.h"
#include <fmt/core.h>

namespace Ceres
{
    PhysicsComponent::PhysicsComponent(const IEntity& parent, IPrimitive* primitive)
        :IComponent(parent, std::type_index(typeid(PhysicsComponent))), _primitive(primitive)
    {}

    PhysicsComponent::~PhysicsComponent()
    {
        delete _primitive;
    }

    bool PhysicsComponent::RecieveMessage(Message* message)
    {
        if (message->Type == "Position")
        {
            Transform newTransform = _primitive->GetTransform();
            newTransform.SetPosition(message->GetData<Vector3>());
            _primitive->SetTransform(newTransform);
        }
        else if (message->Type == "Rotate")
        {
            Transform newTransform = _primitive->GetTransform();
            newTransform.SetRotation(newTransform.GetRotation() + message->GetData<Vector3>());
            _primitive->SetTransform(newTransform);
        }
        else if (message->Type == "Scale")
        {
            Transform newTransfrom = _primitive->GetTransform();
            newTransfrom.SetScale(message->GetData<Vector3>());
            _primitive->SetTransform(newTransfrom);
        }
        else if (message->Type == "Acceleration")
        {
            Acceleration = message->GetData<Vector3>();
            return true;
        }
        else if (message->Type == "Pause")
        {
            Paused = !Paused;
            return true;
        }
        return false;
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
        _parent.SendMessage(Message::Write<Vector3>("Position", &newPosition));
    }

    float PhysicsComponent::SemiMajorAxis() const
    {
        return _primitive->SemiMajorAxis();
    }

    IPrimitive*& PhysicsComponent::GetPrimitive()
    {
        return _primitive;
    }
}