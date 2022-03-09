#pragma once

#include "Base/IComponent.h"

#include "../Common/Matrix.h"

namespace Ceres
{
    class CameraComponent : public IComponent
    {
        public:
            CameraComponent();
            CameraComponent(int width, int height, float fOV, float near, float far);
            ~CameraComponent();

            bool virtual RecieveMessage(Message& message) override;
            const Matrix& GetMatrix();
            const Matrix& GetRotationMatrix();
            const Vector3 GetPosition() const;
            const Vector3 GetFocalPoint() const;

            const float GetFOV() const;
            void SetFOV(const float fOV);

            void SetResolution(unsigned int width, unsigned int height);

            void SetClipRange(float start, float end);

            Vector3 Position;
            Vector3 Rotation = Vector3(-0.55f, 0.0f, 0.0f);
            Vector3 Offset = Vector3(0.0f, -7.0f, 0.0f);

        private:
            void setPosition(const Vector3& position);
            void translate(const Vector3& translation);
            void rotate(const Vector3& rotation);

            Matrix _matrix;
            Matrix _viewRotation;
            Matrix _projection;
            Vector3 _velocityOffset;
            /// The velocity of our parent, for when we are tracking slightly behind the object
            Vector3 _velocity;

            bool _regenViewMatrix = true;
            bool _regenRotationMatrix = true;
            bool _regenProjectionMatrix = true;

            float _fOV = 90.0f;
            unsigned int _width;
            unsigned int _height;
            float _clipStart = 0.1f;
            float _clipEnd = 100.0f;
    };
}