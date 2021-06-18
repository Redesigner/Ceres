#include "CameraComponent.h"

namespace Ceres
{
    CameraComponent::CameraComponent(const IEntity& parent)
        :IComponent(parent, std::type_index(typeid(CameraComponent)))
    {
        Direction = Vector3(0, -10, -1);
        Offset = Vector3(0, 10, 1);
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
        return _matrix;
    }

    const Matrix& CameraComponent::GetRotationMatrix()
    {
        return _viewRotation;
    }

    const Matrix& CameraComponent::GetPositionMatrix()
    {
        return _viewPosition;
    }

    // Private methods
    void CameraComponent::setPosition(const Vector3& position)
    {
        Position = position;
    }

    void CameraComponent::translate(const Vector3& translation)
    {
        Position += translation;
        updateTransform();
    }

    void CameraComponent::updateTransform()
    {
        _viewRotation = Matrix::LookAt(Vector3(0), Direction, Vector3::Up());
        _viewPosition = Matrix::Translation(-Position.X - Offset.X, -Position.Y - Offset.Y, -Position.Z - Offset.Z);
        _matrix = _viewPosition * _viewRotation;
    }
}