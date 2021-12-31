#include "CameraComponent.h"

namespace Ceres
{
    CameraComponent::CameraComponent(const IEntity& parent)
        :IComponent(parent, std::type_index(typeid(CameraComponent)))
    {
        Direction = Vector3(0, -5, -5);
        Offset = Vector3(0, 5, 5);
    }

    CameraComponent::~CameraComponent()
    {

    }

    bool CameraComponent::RecieveMessage(Message* message)
    {
        if(message->Type == "Translate")
        {
            _translate(message->GetData<Vector3>());
            return true;
        }
        else if (message->Type == "Position")
        {
            _setPosition(message->GetData<Vector3>());
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
    void CameraComponent::_setPosition(const Vector3& position)
    {
        Position = position;
        _updateTransform();
    }

    void CameraComponent::_translate(const Vector3& translation)
    {
        Position += translation;
        _updateTransform();
    }

    void CameraComponent::_updateTransform()
    {
        _viewRotation = Matrix::LookAt(Vector3(0), Direction.Normalize(), Vector3::Up());
        _viewPosition = Matrix::Translation(-Position.X - Offset.X, -Position.Y - Offset.Y, -Position.Z - Offset.Z);
        _matrix = _viewPosition * _viewRotation;
    }
}