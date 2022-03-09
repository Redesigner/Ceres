#include "ControllerComponent.h"

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

        inputHandler.BindInput(Button::Key_space,  [this]() { sendMessage(Message::Write("Jump")); });
        inputHandler.BindInput(Button::Key_pause, [this]() { sendMessage(Message::Write("Pause")); });
    }

    ControllerComponent::~ControllerComponent()
    {}

    bool ControllerComponent::RecieveMessage(Message& message)
    {
        if (message.Type == "CameraRotation")
        {
            const float pi = 3.14159f;
            float angleX = message.GetData<Vector3>().X / 640.0f;
            _rotation -= angleX;
            if (_rotation > pi)
            {
                _rotation -= 2 * pi;
            }
            if (_rotation < -pi)
            {
                _rotation += 2 * pi;
            }
            return true;
        }
        return false;
    }

    void ControllerComponent::Update(double seconds)
    {
        Vector2 inputAxis = _inputHandler.GetAxis2DValue("Movement");
        float rotationInput = _inputHandler.GetAxisValue("Rotation");

        // Using a RH coord system with z up, x and y are switched from the traditional 2D values...
        Vector2 input = Vector2(
            ( (inputAxis.X * std::cos(_rotation)) + (-inputAxis.Y * std::sin(_rotation)) ),
            ( (inputAxis.Y * std::cos(_rotation)) + (inputAxis.X * std::sin(_rotation)) ));

        if (input.LengthSquared() > 0.0f)
        {
            const float pi = 3.14159f;
            float desiredRotation = std::atan2f(input.Y, input.X) + pi / 2;
            float rotationDifference = desiredRotation - _ownerRotation;
            if (rotationDifference > pi)
            {
                rotationDifference -= 2 * pi;
            }
            else if (rotationDifference < -pi)
            {
                rotationDifference += 2 * pi;
            }
            float deltaRotation = (std::signbit(rotationDifference) ? -1 : 1) * rotationSpeed * seconds;
            if (std::abs(deltaRotation) > std::abs(rotationDifference))
            {
                deltaRotation = rotationDifference;
            }
            _ownerRotation += deltaRotation;
            if (_ownerRotation > pi)
            {
                _ownerRotation -= 2 * pi;
            }
            if (_ownerRotation < -pi)
            {
                _ownerRotation += 2 * pi;
            }
            Vector3 rotation = Vector3(deltaRotation, 0.0f, 0.0f);
            sendMessage(Message::Write("RotateMesh", rotation));
            //sendMessage(Message::Write("CameraRotation", Vector3((desiredRotation - _rotation), 0.0f, 0.0f)) );
        }

        sendMessage(Message::Write("AddInput", input));
    }
}