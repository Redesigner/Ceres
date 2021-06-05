#pragma once

#include "Matrix.h"
#include "Vector3.h"

namespace Ceres
{
    class Transform
    {
        public:
            Transform();
            ~Transform();

            void SetPosition(const Vector3& position);
            Vector3 GetPosition() const;

            void SetRotation(const Vector3& rotation);
            Vector3 GetRotation() const;

            void SetScale(const Vector3& scale);
            Vector3 GetScale() const;

            Matrix GetMatrix() const;

        private:
            void calculateMatrix();

            Matrix _matrix;
            Vector3 _position;
            Vector3 _rotation;
            Vector3 _scale;
    };
}