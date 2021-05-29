#pragma once

namespace Ceres
{
    struct Matrix
    {
        public:
            Matrix();
            Matrix(
                float m11, float m12, float m13, float m14,
                float m21, float m22, float m23, float m24,
                float m31, float m32, float m33, float m34,
                float m41, float m42, float m43, float m44);

            static Matrix Translation(float x, float y, float z);

            static Matrix RotationAlongX(float angle);
            static Matrix RotationAlongY(float angle);
            static Matrix RotationAlongZ(float angle);
            static Matrix RotationFromEuler(float roll, float pitch, float yaw);

            static Matrix TranslationScale(float xPos, float yPos, float zPos, float xScale, float yScale, float zScale);
            static Matrix Scale(float x, float y, float z);

            static Matrix Identity();
            static Matrix Zero();
            static Matrix Perspective(float width, float height, float near, float far);

            Matrix operator*(const Matrix& b);

            float M[4][4];
    };
}