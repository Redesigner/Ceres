#pragma once

#include "Vector3.h"

#include <string>

namespace Ceres
{
    struct Matrix
    {
        public:
            Matrix(
                float m11, float m12, float m13, float m14,
                float m21, float m22, float m23, float m24,
                float m31, float m32, float m33, float m34,
                float m41, float m42, float m43, float m44);

            Matrix();
            ~Matrix();
            
            /// Matrix representing a translation along x, y, and z.
            static Matrix Translation(float x, float y, float z);

            /// Matrix representing a rotation, in radians, about the X-axis.
            static Matrix RotationAlongX(float angle);
            /// Matrix representing a rotation, in radians, about the Y-axis.
            static Matrix RotationAlongY(float angle);
            /// Matrix representing a rotation, in radians, about the Z-axis.
            static Matrix RotationAlongZ(float angle);
            /// Matrix representing an Euler rotation.
            /// Rotations are made from left to right.
            static Matrix RotationFromEuler(float roll, float pitch, float yaw);

            /// Matrix representing a translation and scale.
            /// Faster than multiplying two individual matrices;
            static Matrix TranslationScale(float xPos, float yPos, float zPos, float xScale, float yScale, float zScale);
            /// Matrix representing a non-uniform scale along each individual axis.
            static Matrix Scale(float x, float y, float z);
            /// The identity matrix. Any matrix or vector multiplied by this is itself.
            static Matrix Identity();
            /// Matrix where all values are zero.
            static Matrix Zero();

            /// Perspective transformation Matrix.
            static Matrix Perspective(float width, float height, float fOV, float near, float far);
            static Matrix Orthographic(float right, float left, float top, float bottom, float near, float far);
            static Matrix Orthographic(float width, float height, float near, float far);
            /// The inverse transformation matrix for a camera, looking from 'eyePos' to 'target'.
            static Matrix LookAt(const Vector3& eyePos, const Vector3& target, const Vector3& up);
            /// The standard change of basis matrix from OpenGL coordinates to Z-up, Y+ forward.
            static Matrix Basis();
            static Matrix ChangeOfBasis(Vector3& x, Vector3& y, Vector3& z);
            
            /// Transposition of a Matrix
            Matrix Transpose() const;

            /// A debug-friendly string representation of a matrix.
            std::string ToString() const;

            Matrix operator*(const Matrix& b);
            Vector3 operator*(const Vector3& b);

            operator float*();

            float M[4][4];
    };
}