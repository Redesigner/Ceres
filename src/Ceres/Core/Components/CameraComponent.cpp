#include "CameraComponent.h"

namespace Ceres
{
    CameraComponent::CameraComponent(int width, int height, float fOV, float near, float far)
        :IComponent(std::type_index(typeid(CameraComponent))), _width(width), _height(height), _fOV(fOV), _clipStart(near), _clipEnd(far)
    {
        addMessageHandler("Translate", [](IComponent* component, Message& message)
            {
                CameraComponent* camera = static_cast<CameraComponent*>(component);
                camera->translate(message.GetData<Vector3>());
            });
        addMessageHandler("Position", [](IComponent* component, Message& message)
            {
                CameraComponent* camera = static_cast<CameraComponent*>(component);
                camera->setPosition(message.GetData<Vector3>());
            });
        addMessageHandler("CameraRotation", [](IComponent* component, Message& message)
            {
                CameraComponent* camera = static_cast<CameraComponent*>(component);
                float roll = 0.0f;
                float pitch = -message.GetData<Vector3>().Y / static_cast<float>(camera->_height);
                // This should really be screen width, but currently the controller component can't tell what that is, so it's fixed for now
                float yaw = message.GetData<Vector3>().X / 640.0f;
                camera->rotate(Vector3(pitch, roll, -yaw));
            });
        addMessageHandler("Velocity", [](IComponent* component, Message& message)
            {
                CameraComponent* camera = static_cast<CameraComponent*>(component);
                const float velocityScale = 0.05f;
                const float a = 0.25f;
                const float b = 1.0f - a;
                camera->_velocity = message.GetData<Vector3>() * a + camera->_velocity * b;
                camera->_velocityOffset = camera->_velocity * velocityScale;
                camera->_regenViewMatrix = true;
            });
    }

    CameraComponent::CameraComponent()
        :CameraComponent(0, 0, 90.0f, 0.5f, 30.0f)
    {
    }

    CameraComponent::~CameraComponent()
    {}

    const Matrix& CameraComponent::GetMatrix()
    {
        if (_regenProjectionMatrix)
        {
            _projection = Matrix::Perspective(_width, _height, _fOV, _clipStart, _clipEnd);
            _regenProjectionMatrix = false;
        }
        if (_regenViewMatrix)
        {
            const float velocityScale = 0.05f;
            Matrix rotation = Matrix::RotationFromEuler(Rotation.Z, Rotation.Y, Rotation.X);
            _matrix = Matrix::LookAt((rotation * Offset) + FocalPoint + _velocityOffset, FocalPoint + _velocityOffset, Vector3::Up()) * _projection;
            _regenViewMatrix = false;
        }
        return _matrix;
    }

    const Matrix& CameraComponent::GetRotationMatrix()
    {
        if (_regenProjectionMatrix)
        {
            _projection = Matrix::Perspective(_width, _height, _fOV, _clipStart, _clipEnd);
            _regenProjectionMatrix = false;
        }
        if (_regenRotationMatrix)
        {
            Matrix rotation = Matrix::RotationFromEuler(Rotation.Z, Rotation.Y, Rotation.X);
            _viewRotation = Matrix::LookAt(Vector3::Zero(), (rotation * Vector3(0, 1, 0)), Vector3::Up()) * _projection;
            _regenRotationMatrix = false;
        }
        return _viewRotation;
    }

    const Vector3 CameraComponent::GetPosition() const
    {
        return FocalPoint + (Matrix::RotationFromEuler(Rotation.Z, Rotation.Y, Rotation.X) * Offset) + _velocityOffset;
    }

    const Vector3 CameraComponent::GetFocalPoint() const
    {
        return FocalPoint;
    }

    const float CameraComponent::GetFOV() const
    {
        return _fOV;
    }

    void CameraComponent::SetFOV(const float fOV)
    {
        if (_fOV != fOV)
        {
            _fOV = fOV;
            _regenViewMatrix = true;
        }
    }

    void CameraComponent::SetResolution(unsigned int width, unsigned int height)
    {
        if (_width != width || _height != height)
        {
            _width = width;
            _height = height;
            _regenViewMatrix = true;
        }
    }

    /// Sets the clipping range for the camera, recalculating the relevant transformation matrix if necessary
    /// Negative values will be set to 0
    /// The end distance must be greater than the start, or it will be forced to be the start distance plus 0.01

    void CameraComponent::SetClipRange(float start, float end)
    {
        if (start < 0.0f)
        {
            start = 0.0f;
        }
        if (end < start)
        {
            end = start + 0.01f;
        }
        _regenViewMatrix = true;
    }

    // Private methods
    void CameraComponent::setPosition(const Vector3& position)
    {
        FocalPoint = position;
        _regenViewMatrix = true;
    }

    void CameraComponent::translate(const Vector3& translation)
    {
        if (translation != Vector3::Zero())
        {
            FocalPoint += translation;
            _regenViewMatrix = true;
        }
    }

    void CameraComponent::rotate(const Vector3& rotation)
    {
        if (rotation != Vector3::Zero())
        {
            if (Rotation.X + rotation.X < 1.57f && Rotation.X + rotation.X > -1.57f)
            {
                Rotation.X += rotation.X;
            }
            Rotation.Z += rotation.Z;
            _regenRotationMatrix = true;
            _regenViewMatrix = true;
        }
    }
}