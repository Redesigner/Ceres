#include "ControllerComponent.h"

#include "../Common/Math.h"
#include "../Common/Vector2.h"
#include "../Common/Vector3.h"
#include "../Entities/Base/IEntity.h"

#include <cmath>
#include <fmt/core.h>

namespace Ceres
{
    const float rotationSpeed = 5.0f;
    ControllerComponent::ControllerComponent(InputHandler& inputHandler)
        :IComponent(std::type_index(typeid(ControllerComponent))), _inputHandler(inputHandler)
    {
        std::function<void(int, int)> l = [this](int x, int y)
        {
            sendMessage(Message::Write<Vector3>("CameraRotation", Vector3(x, y, 0)) );
        };
        inputHandler.BindCursorInput(l);

        inputHandler.BindAction("Jump",  [this]() { sendMessage(Message::Write("Jump")); });
        inputHandler.BindAction("Pause", [this]() { sendMessage(Message::Write("Pause")); });

        addMessageHandler("CameraRotation", [](IComponent* component, Message& message)
            {
                ControllerComponent* controller = static_cast<ControllerComponent*>(component);
                float angleX = message.GetData<Vector3>().X / 640.0f;
                controller->_rotation = Math::ClampRadians(controller->_rotation - angleX);
            });
    }

    ControllerComponent::~ControllerComponent()
    {}

    void ControllerComponent::Update(double seconds)
    {
        Vector2 inputAxis = _inputHandler.GetAxis2DValue("Movement");
        float rotationInput = _inputHandler.GetAxisValue("Rotation");

        // Using a RH coord system with z up, x and y are switched from the traditional 2D values...
        Vector2 input = Vector2(
            ( (inputAxis.X * std::cos(_rotation)) + (-inputAxis.Y * std::sin(_rotation)) ),
            ( (inputAxis.Y * std::cos(_rotation)) + (inputAxis.X * std::sin(_rotation)) ));

        float i2 = input.LengthSquared();
        if (i2 > 0.0f)
        {
            float desiredRotation = std::atan2f(input.Y, input.X) + Math::Tau();
            float rotationDifference = Math::ClampRadians(desiredRotation - _ownerRotation);
            float deltaRotation = (std::signbit(rotationDifference) ? -1 : 1) * rotationSpeed * std::sqrtf(i2) * seconds;
            if (std::abs(deltaRotation) > std::abs(rotationDifference))
            {
                deltaRotation = rotationDifference;
            }
            _ownerRotation =  Math::ClampRadians(_ownerRotation + deltaRotation);
            Vector3 rotation = Vector3(deltaRotation, 0.0f, 0.0f);
            sendMessage(Message::Write("RotateMesh", rotation));
        }

        sendMessage(Message::Write("AddInput", input));
    }
}