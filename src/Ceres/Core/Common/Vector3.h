#pragma once

namespace Ceres
{
    struct Vector3
    {
        public:
            Vector3(float x, float y, float z);
            Vector3(float a);
            Vector3(const Vector3& vector);
            ~Vector3();

            float X, Y, Z;

            static Vector3 Zero();
            static Vector3 Up();
            
            float Length();
            float LengthSquared();
            Vector3 Normalize();
            Vector3 Cross(const Vector3& vector);
            Vector3 Dot(const Vector3& vector);

            Vector3& operator+=(const Vector3& vector);
            Vector3 operator+(const Vector3& vector);
            Vector3& operator-=(const Vector3& vector);
            Vector3 operator-(const Vector3& vector);
            Vector3 operator*(const Vector3& vector);
            Vector3 operator*(float scalar);
            Vector3 operator/(const Vector3& vector);
            Vector3 operator/(float scalar);

            bool operator==(const Vector3& vector);
        private:
    };
}