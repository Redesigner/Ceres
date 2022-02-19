#include "CameraComponent.h"

namespace Ceres
{
    CameraComponent::CameraComponent(const IEntity& parent)
        :IComponent(parent, std::type_index(typeid(CameraComponent)))
    {
        Rotation = Vector3(0, 0.785f, 0);
        Offset = Vector3(-7, 0, 0);
    }

    CameraComponent::~CameraComponent()
    {}

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
        else if (message->Type == "CameraRotation")
        {
            float pitch = message->GetData<Vector3>().Y / 480.0f;
            float yaw = message->GetData<Vector3>().Z / 640.0f;
            Vector3 deltaRotation = Vector3(0, pitch, -yaw);
            if (Rotation.Y + deltaRotation.Y < 1.57f && Rotation.Y + deltaRotation.Y > -1.57f)
            {
                Rotation.Y += deltaRotation.Y;
            }
            Rotation.X += deltaRotation.Z;
            _updateTransform();
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

    const Vector3 CameraComponent::GetPosition()
    {
        return Position + (Matrix::RotationFromEuler(Rotation.X, Rotation.Y, Rotation.Z) * Offset);
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
        _viewRotation = Matrix::RotationFromEuler(Rotation.X, Rotation.Y, Rotation.Z);
        _matrix = Matrix::LookAt((_viewRotation * Offset) + Position, Position, Vector3::Up());
        _viewRotation = Matrix::LookAt(Vector3::Zero(), (_viewRotation * Vector3(1, 0, 0)), Vector3::Up());
    }
}