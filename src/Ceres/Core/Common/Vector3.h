#pragma once

#include <string>

namespace Ceres
{
    struct Vector3
    {
        public:
            Vector3(float x, float y, float z);
            Vector3(float a);
            Vector3(const Vector3& vector);
            Vector3();
            ~Vector3();

            float X, Y, Z;

            static Vector3 Zero();
            static Vector3 Up();
            static float Epsilon() { return 0.0001; }
            
            float Length() const;
            float LengthSquared() const;
            Vector3 Normalize() const;
            Vector3 Cross(const Vector3& vector) const;
            Vector3 Triple(const Vector3& vector) const;
            float Dot(const Vector3& vector) const;
            double Angle(const Vector3& vector) const;

            Vector3& operator+=(const Vector3& vector);
            Vector3 operator+(const Vector3& vector) const;
            Vector3& operator-=(const Vector3& vector);
            Vector3 operator-(const Vector3& vector) const;
            Vector3 operator*(const Vector3& vector) const;
            Vector3 operator*(float scalar) const;
            Vector3 operator/(const Vector3& vector) const;
            Vector3 operator/(float scalar) const;
            Vector3 operator-() const;
            
            std::string ToString() const;

            bool operator==(const Vector3& vector) const;
            bool operator!=(const Vector3& vector) const;
        private:
    };

    Vector3 operator*(float scalar, const Vector3& vector);
}