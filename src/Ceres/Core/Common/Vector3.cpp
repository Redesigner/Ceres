#include "Vector3.h"

#include <cmath>

namespace Ceres
{
    Vector3::Vector3(float x, float y, float z)
        : X(x), Y(y), Z(z){}

    Vector3::Vector3(float a)
        :X(a), Y(a), Z(a){}

    Vector3::Vector3(const Vector3& vector)
        :X(vector.X), Y(vector.Y), Z(vector.Z){}

    Vector3::~Vector3() {}


    float Vector3::Length()
    {
        return std::sqrtf(LengthSquared());
    }

    float Vector3::LengthSquared()
    {
        return (X * X) + (Y * Y) + (Z * Z);
    }

    Vector3 Vector3::Zero()
    {
        return Vector3(0);
    }

    Vector3 Vector3::Up()
    {
        return Vector3(0, 1, 0);
    }

    Vector3 Vector3::Normalize()
    {
        return *this / Length();
    }

    Vector3& Vector3::operator+=(const Vector3& vector)
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
        return *this;
    }

    Vector3 Vector3::operator+(const Vector3& vector)
    {
        return Vector3(*this) += vector;
    }

    Vector3& Vector3::operator-=(const Vector3& vector)
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
        return *this;
    }

    Vector3 Vector3::operator-(const Vector3& vector)
    {
        return Vector3(*this) -= vector;
    }

    Vector3 Vector3::operator*(const Vector3& vector)
    {
        return Vector3(X * vector.X, Y * vector.Y, Z * vector.Z);
    }

    Vector3 Vector3::operator*(float scalar)
    {
        return Vector3(X * scalar, Y * scalar, Z * scalar);
    }

    Vector3 Vector3::operator/(const Vector3& vector)
    {
        return Vector3(X / vector.X, Y / vector.Y, Z / vector.Z);
    }

    Vector3 Vector3::operator/(float scalar)
    {
        return Vector3(X / scalar, Y / scalar, Z / scalar);
    }

    bool Vector3::operator==(const Vector3& vector)
    {
        return (X == vector.X) && (Y == vector.Y) && (Z == vector.Z);
    }
}