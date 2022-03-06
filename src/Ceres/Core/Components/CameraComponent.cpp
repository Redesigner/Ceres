#include "CameraComponent.h"

namespace Ceres
{
    CameraComponent::CameraComponent()
        :IComponent(std::type_index(typeid(CameraComponent)))
    {
        const float pitch = -0.55f;
        Rotation = Vector3(pitch, 0.0f, 0.0f);
        Offset = Vector3(0.0f, -7.0f, 0.0f);
    }

    CameraComponent::~CameraComponent()
    {}

    bool CameraComponent::RecieveMessage(Message& message)
    {
        if(message.Type == "Translate")
        {
            translate(message.GetData<Vector3>());
            return true;
        }
        else if (message.Type == "Position")
        {
            setPosition(message.GetData<Vector3>());
            return true;
        }
        else if (message.Type == "CameraRotation")
        {
            float roll = 0.0f;
            float pitch = -message.GetData<Vector3>().Y / 480.0f;
            float yaw = message.GetData<Vector3>().X / 640.0f;
            Vector3 deltaRotation = Vector3(pitch, roll, -yaw);
            if (Rotation.X + deltaRotation.X < 1.57f && Rotation.X + deltaRotation.X > -1.57f)
            {
                Rotation.X += deltaRotation.X;
            }
            Rotation.Z += deltaRotation.Z;
            updateTransform();
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
    void CameraComponent::setPosition(const Vector3& position)
    {
        Position = position;
        updateTransform();
    }

    void CameraComponent::translate(const Vector3& translation)
    {
        Position += translation;
        updateTransform();
    }

    void CameraComponent::updateTransform()
    {
        Matrix rotation = Matrix::RotationFromEuler(Rotation.Z, Rotation.Y, Rotation.X);
        _matrix = Matrix::LookAt((rotation * Offset) + Position, Position, Vector3::Up());
        _viewRotation = Matrix::LookAt(Vector3::Zero(), (rotation * Vector3(0, 1, 0)), Vector3::Up());
    }
}