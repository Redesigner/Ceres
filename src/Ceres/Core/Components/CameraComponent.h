#pragma once

#include "Base/IComponent.h"

#include "../Common/Matrix.h"

namespace Ceres
{
    class CameraComponent : public IComponent
    {
        public:
            CameraComponent();
            ~CameraComponent();

            bool virtual RecieveMessage(Message& message) override;
            const Matrix& GetMatrix();
            const Matrix& GetRotationMatrix();
            const Matrix& GetPositionMatrix();
            const Vector3 GetPosition();

            Vector3 Position;
            Vector3 Rotation;
            Vector3 Offset;

        private:
            void setPosition(const Vector3& position);
            void translate(const Vector3& translation);
            void updateTransform();

            Matrix _matrix;
            Matrix _viewPosition;
            Matrix _viewRotation;
            Vector3 _velocityOffset;
    };
}