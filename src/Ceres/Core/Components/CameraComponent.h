#pragma once

#include "Base/IComponent.h"

#include "../Common/Matrix.h"

namespace Ceres
{
    class CameraComponent : public IComponent
    {
        public:
            CameraComponent(const IEntity& parent);
            ~CameraComponent();

            bool virtual RecieveMessage(Message* message) override;
            const Matrix& GetMatrix();
            const Matrix& GetRotationMatrix();
            const Matrix& GetPositionMatrix();

            Vector3 Position;
            Vector3 Rotation;
            Vector3 Offset;

        private:
            void _setPosition(const Vector3& position);
            void _translate(const Vector3& translation);
            void _updateTransform();

            Matrix _matrix;
            Matrix _viewPosition;
            Matrix _viewRotation;
    };
}