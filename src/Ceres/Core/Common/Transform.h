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

            void SetPosition(Vector3 position);
            const Vector3& GetPosition();

            void SetRotation(Vector3 rotation);
            const Vector3& GetRotation();

            void SetScale(Vector3 scale);
            const Vector3& GetScale();

            const Matrix& GetMatrix() const;

        private:
            void calculateMatrix();

            Matrix _matrix;
            Vector3 _position;
            Vector3 _rotation;
            Vector3 _scale;
    };
}