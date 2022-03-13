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

    bool MovementComponent::ReceiveMessage(Message& message)
    {
        if (message.Type == "AddInput")
        {
            const float accelerationRate = 50.0f;
            const float airControl = 0.2f;
            Vector2 input = message.GetData<Vector2>();
            Vector3 acceleration = Vector3(input.X, input.Y, 0.0f) * accelerationRate;
            if (!_grounded)
            {
                acceleration = acceleration * airControl;
            }
            sendMessage(Message::Write("Acceleration", acceleration));
            return true;
        }
        if (message.Type == "Jump")
        {
            if (_grounded)
            {
                const float jumpForce = 500.0f;
                _grounded = false;
                sendMessage(Message::Write("Acceleration", Vector3(0.0f, 0.0f, jumpForce)));
            }
            return true;
        }
        if (message.Type == "Landed")
        {
            _grounded = message.GetData<bool>();
            return true;
        }
        return false;
    }
}