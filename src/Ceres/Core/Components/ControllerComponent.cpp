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
            sendMessage(Message::Write<Vector3>("CameraRotation", &Vector3(x, y, 0)) );
        };
        inputHandler.BindCursorInput(l);

        std::function<void()> jump = [this]()
        {
            if (this->_canJump)
            {
                sendMessage(Message::Write<Vector3>("AddInput", &Vector3(0.0f, 0.0f, 500.0f)));
                this->_canJump = false;
            }
        };
        inputHandler.BindInput(Button::Key_space, jump);
    }

    ControllerComponent::~ControllerComponent()
    {}

    bool ControllerComponent::RecieveMessage(Message* message)
    {
        if (message->Type == "CameraRotation")
        {
            float angleX = message->GetData<Vector3>().X / 640.0f;
            _rotation -= angleX;
        }
        if (message->Type == "Landed")
        {
            _canJump = true;
        }
        return false;
    }

    void ControllerComponent::Update(double seconds)
    {
        Vector2 inputAxis = _inputHandler.GetAxis2DValue("Movement");
        float rotationInput = _inputHandler.GetAxisValue("Rotation");

        // Using a RH coord system with z up, x and y are switched from the traditional 2D values...
        Vector3 inputForce = Vector3(
            ( (inputAxis.X * std::cos(_rotation)) + (-inputAxis.Y * std::sin(_rotation)) ) * 10,
            ( (inputAxis.Y * std::cos(_rotation)) + (inputAxis.X * std::sin(_rotation)) ) * 10,
            0);

        sendMessage(Message::Write<Vector3>("AddInput", &inputForce));
        sendMessage(Message::Write<Vector3>("Rotate", &Vector3(.1f * rotationInput, 0, 0)));
    }
}