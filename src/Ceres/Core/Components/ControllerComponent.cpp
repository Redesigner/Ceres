#include "ControllerComponent.h"

#include "../Common/Vector2.h"
#include "../Common/Vector3.h"
#include "../Entities/Base/IEntity.h"

namespace Ceres
{
    ControllerComponent::ControllerComponent(const IEntity& parent, const InputHandler& inputHandler)
        :IComponent(parent, std::type_index(typeid(ControllerComponent))), _inputHandler(inputHandler)
    {}

    ControllerComponent::~ControllerComponent()
    {
    }

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
    
        if (rotationInput != 0)
        {
            _parent.SendMessage(Message::Write<int>("Print", 0));
        }
    }
}