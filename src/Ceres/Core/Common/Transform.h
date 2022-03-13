#pragma once

#include "Matrix.h"
#include "Vector3.h"

namespace Ceres
{
    class Transform
    {
        public:
            /// A collection of matrices representing world transformation.
            /// Handles recalculation only when necessary.
            Transform();
            ~Transform();

            void SetPosition(const Vector3& position);
            /// The transformation's position component, as a Vector.
            Vector3 GetPosition() const;
            /// The transformation's position component, as a Matrix.
            Matrix GetPositionMatrix() const;

            void SetRotation(const Vector3& rotation);
            Vector3 GetRotation() const;
            Matrix GetRotationMatrix() const;

            void SetScale(const Vector3& scale);
            Vector3 GetScale() const;
            Matrix GetScaleMatrix() const;

            /// Returns the complete transformation matrix.
            Matrix GetMatrix() const;
            Matrix GetInverse() const;

        private:
            void calculateMatrix();

            Matrix _matrix;
            
            Matrix _positionMatrix;
            Matrix _rotationMatrix;
            Matrix _scaleMatrix;

            Vector3 _position;
            Vector3 _rotation;
            Vector3 _scale;
    };
}