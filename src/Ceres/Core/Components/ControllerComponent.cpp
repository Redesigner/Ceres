#include "ControllerComponent.h"

#include "../Common/Vector2.h"
#include "../Common/Vector3.h"
#include "../Entities/Base/IEntity.h"

namespace Ceres
{
    ControllerComponent::ControllerComponent(const IEntity& parent, const InputHandler& inputHandler)
        :IComponent(parent), _inputHandler(inputHandler)
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
        Vector2 inputAxis = _inputHandler.GetAxisValue("test");
        Vector3 testPos = Vector3(inputAxis.X * seconds * 10, 0, inputAxis.Y * seconds * -10);
        _parent.SendMessage(Message::Write<Vector3>("Translate", &testPos));
    }
}