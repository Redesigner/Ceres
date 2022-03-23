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
    {
        addMessageHandler("AddInput", [](IComponent* component, Message& message)
            {
                MovementComponent* movement = static_cast<MovementComponent*>(component);
                const float accelerationRate = 50.0f;
                const float airControl = 0.2f;
                Vector2 input = message.GetData<Vector2>();
                Vector3 acceleration = Vector3(input.X, input.Y, 0.0f) * accelerationRate;
                if (!movement->_grounded)
                {
                    acceleration = acceleration * airControl;
                }
                movement->sendMessage(Message::Write("Acceleration", acceleration));
            });

        addMessageHandler("Jump", [](IComponent* component, Message& message)
            {
                MovementComponent* movement = static_cast<MovementComponent*>(component);
                if (movement->_grounded)
                {
                    const float jumpForce = 500.0f;
                    movement->_grounded = false;
                    movement->sendMessage(Message::Write("Acceleration", Vector3(0.0f, 0.0f, jumpForce)));
                }
            });

        addMessageHandler("Landed", [](IComponent* component, Message& message)
            {
                MovementComponent* movement = dynamic_cast<MovementComponent*>(component);
                movement->_grounded = message.GetData<bool>();
            });
    }

    MovementComponent::~MovementComponent()
    {}
}