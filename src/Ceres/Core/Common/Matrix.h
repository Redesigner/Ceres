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
            
            static Matrix Translation(float x, float y, float z);

            static Matrix RotationAlongX(float angle);
            static Matrix RotationAlongY(float angle);
            static Matrix RotationAlongZ(float angle);
            static Matrix RotationFromEuler(float roll, float pitch, float yaw);

            static Matrix TranslationScale(float xPos, float yPos, float zPos, float xScale, float yScale, float zScale);
            static Matrix Scale(float x, float y, float z);

            static Matrix Identity();
            static Matrix Zero();

            static Matrix Perspective(float width, float height, float fOV, float near, float far);
            static Matrix LookAt(const Vector3& eyePos, const Vector3& target, const Vector3& up);
            
            Matrix Transpose() const;

            std::string ToString() const;

            Matrix operator*(const Matrix& b);
            Vector3 operator*(const Vector3& b);

            operator float*();

            float M[4][4];
    };
}