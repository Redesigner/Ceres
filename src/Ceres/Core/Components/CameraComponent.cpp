#include "CameraComponent.h"

namespace Ceres
{
    CameraComponent::CameraComponent(const IEntity& parent)
        :IComponent(parent)
    {
        Offset = Vector3(0, 5, 5);
    }

    CameraComponent::~CameraComponent()
    {

    }

    bool CameraComponent::RecieveMessage(Message* message)
    {
        if(message->Type == "Translate")
        {
            translate(message->GetData<Vector3>());
            return true;
        }
        else
        {
            return false;
        }
    }

    const Matrix& CameraComponent::GetMatrix()
    {
        return _viewMatrix;
    }

    // Private methods
    void CameraComponent::setPosition(const Vector3& position)
    {
        TargetPosition = position;
    }

    void CameraComponent::translate(const Vector3& translation)
    {
        TargetPosition += translation;
        updateTransform();
    }

    void CameraComponent::updateTransform()
    {
        _viewMatrix = Matrix::LookAt(TargetPosition + Offset, TargetPosition, Vector3::Up());
    }
}