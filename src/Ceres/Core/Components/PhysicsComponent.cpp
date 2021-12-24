#include "PhysicsComponent.h"

#include <fmt/core.h>

namespace Ceres
{
    PhysicsComponent::PhysicsComponent(const IEntity& parent, IPrimitive* primitive)
        :IComponent(parent, std::type_index(typeid(PhysicsComponent))), Primitive(primitive)
    {}

    PhysicsComponent::~PhysicsComponent()
    {
        delete Primitive;
    }

    bool PhysicsComponent::RecieveMessage(Message* message)
    {
        if (message->Type == "Translate")
        {
            Primitive->Transform.SetPosition(Primitive->Transform.GetPosition() + message->GetData<Vector3>());
            return true;
        }
        else if (message->Type == "Rotate")
        {
            Primitive->Transform.SetRotation(Primitive->Transform.GetRotation() + message->GetData<Vector3>());
            return true;
        }
        else if (message->Type == "Print")
        {
            fmt::print("Furthest vertex: {}\n", Primitive->FurthestVertex(Vector3(1, 0, 0)).ToString());
            return true;
        }
        return false;
    }
}