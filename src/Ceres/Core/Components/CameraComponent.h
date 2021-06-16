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

            Vector3 TargetPosition;
            Vector3 Offset;

        private:
            void setPosition(const Vector3& position);
            void translate(const Vector3& translation);
            void updateTransform();

            Matrix _viewMatrix;
    };
}