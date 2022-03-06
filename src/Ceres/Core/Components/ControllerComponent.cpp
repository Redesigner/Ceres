#include "ControllerComponent.h"

#include "../Common/Vector2.h"
#include "../Common/Vector3.h"
#include "../Entities/Base/IEntity.h"

#include <cmath>
#include <fmt/core.h>

namespace Ceres
{
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
            float angleX = message.GetData<Vector3>().X / 640.0f;
            _rotation -= angleX;
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

        sendMessage(Message::Write("AddInput", input));
        sendMessage(Message::Write("Rotate", Vector3(.1f * rotationInput, 0, 0)));
    }
}