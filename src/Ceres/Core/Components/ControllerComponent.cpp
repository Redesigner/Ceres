#include "ControllerComponent.h"

#include "../Common/Vector2.h"
#include "../Common/Vector3.h"
#include "../Entities/Base/IEntity.h"

#include <fmt/core.h>

namespace Ceres
{
    ControllerComponent::ControllerComponent(const IEntity& parent, InputHandler& inputHandler)
        :IComponent(parent, std::type_index(typeid(ControllerComponent))), _inputHandler(inputHandler)
    {
        const IEntity* target = &parent;
        std::function<void(int, int)> l = [target](int x, int y)
        {
            target->SendMessage(Message::Write<Vector3>("CameraRotation", &Vector3(x, y, 0)) );
        };
        inputHandler.BindCursorInput(l);
    }

    ControllerComponent::~ControllerComponent()
    {}

    bool ControllerComponent::RecieveMessage(Message* message)
    {
        return false;
    }

    void ControllerComponent::Update(double seconds)
    {
        Vector2 inputAxis = _inputHandler.GetAxis2DValue("test");
        float verticalInput = _inputHandler.GetAxisValue("Vertical");
        float rotationInput = _inputHandler.GetAxisValue("Rotation");
        // Using a RH coord system with z up, x and y are switched from the traditional 2D values...
        Vector3 velocity = Vector3(
            inputAxis.Y * 10,
            inputAxis.X * -10,
            verticalInput * 2);
        _parent.SendMessage(Message::Write<Vector3>("Velocity", &velocity));
        _parent.SendMessage(Message::Write<Vector3>("Rotate", &Vector3(.1f * rotationInput, 0, 0)));
    }
}