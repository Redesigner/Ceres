#include "ControllerComponent.h"

#include "../Common/Vector2.h"
#include "../Common/Vector3.h"
#include "../Entities/Base/IEntity.h"

#include <cmath>
#include <fmt/core.h>

namespace Ceres
{
    ControllerComponent::ControllerComponent(const IEntity& parent, InputHandler& inputHandler)
        :IComponent(parent, std::type_index(typeid(ControllerComponent))), _inputHandler(inputHandler)
    {
        const IEntity* target = &parent;
        std::function<void(int, int)> l = [target](int x, int y)
        {
            target->SendMessage(Message::Write<Vector3>("CameraRotation", &Vector3(0, y, x)) );
        };
        inputHandler.BindCursorInput(l);
    }

    ControllerComponent::~ControllerComponent()
    {}

    bool ControllerComponent::RecieveMessage(Message* message)
    {
        if (message->Type == "CameraRotation")
        {
            float angleX = message->GetData<Vector3>().X / 640.0f;
            _rotation += angleX;
        }
        return false;
    }

    void ControllerComponent::Update(double seconds)
    {
        Vector2 inputAxis = _inputHandler.GetAxis2DValue("Movement");
        bool isJumping = _inputHandler.ButtonPressed(Button::Key_space);
        float rotationInput = _inputHandler.GetAxisValue("Rotation");

        // Using a RH coord system with z up, x and y are switched from the traditional 2D values...
        Vector3 inputForce = Vector3(
            ( (inputAxis.Y * std::cos(_rotation)) + (-inputAxis.X * std::sin(_rotation)) ) * 10,
            ( (-inputAxis.X * std::cos(_rotation)) - (inputAxis.Y * std::sin(_rotation)) ) * 10,
            isJumping * 20);

        _parent.SendMessage(Message::Write<Vector3>("AddInput", &inputForce));
        _parent.SendMessage(Message::Write<Vector3>("Rotate", &Vector3(.1f * rotationInput, 0, 0)));
    }
}