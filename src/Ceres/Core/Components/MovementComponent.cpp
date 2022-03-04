#include "MovementComponent.h"

#include "../Common/Vector2.h"
#include "../Common/Vector3.h"
#include "../Entities/Base/IEntity.h"

#include <cmath>
#include <fmt/core.h>

namespace Ceres
{
    MovementComponent::MovementComponent()
        :IComponent(std::type_index(typeid(MovementComponent)))
    {}

    MovementComponent::~MovementComponent()
    {}

    bool MovementComponent::RecieveMessage(Message* message)
    {
        if (message->Type == "AddInput")
        {
            //Vector3 gravity = -Vector3::Up() * 9.8f;
            Vector3 acceleration = message->GetData<Vector3>();
            sendMessage(Message::Write<Vector3>("Acceleration", &acceleration));
        }
        return false;
    }
}