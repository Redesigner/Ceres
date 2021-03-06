#include "Vector3.h"

#include <cmath>
#include <fmt/core.h>

namespace Ceres
{
    Vector3::Vector3(float x, float y, float z)
        : X(x), Y(y), Z(z){}

    Vector3::Vector3(float a)
        :X(a), Y(a), Z(a){}

    Vector3::Vector3(const Vector3& vector)
        :X(vector.X), Y(vector.Y), Z(vector.Z){}

    Vector3::Vector3()
        :X(0), Y(0), Z(0)
    {}

    Vector3::~Vector3() {}


    Vector3 Vector3::Zero()
    {
        return Vector3(0);
    }

    Vector3 Vector3::Up()
    {
        return Vector3(0, 0, 1);
    }


    float Vector3::Length() const
    {
        float l2 = LengthSquared();
        if (l2 == 0) { return 0; }
        return std::sqrtf(l2);
    }

    float Vector3::LengthSquared() const
    {
        return (X * X) + (Y * Y) + (Z * Z);
    }

    Vector3 Vector3::Normalize() const
    {
        float l2 = LengthSquared();
        if (l2 == 0.0f) { return Vector3::Zero(); }
        // if the vector is normalized, we can at least skip the sqrt and division
        if (l2 == 1.0f) { return *this; }
        return *this / std::sqrtf(l2);
    }

    Vector3 Vector3::Cross(const Vector3& vector) const
    {
        return Vector3(
            (Y * vector.Z) - (Z * vector.Y),
            (Z * vector.X) - (X * vector.Z),
            (X * vector.Y) - (Y * vector.X)
        );
    }

    Vector3 Vector3::Triple(const Vector3& vector) const
    {
        return Cross(vector).Cross(*this);
    }

    float Vector3::Dot(const Vector3& vector) const
    {
        return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z);
    }

    double Vector3::Angle(const Vector3& vector) const
    {
        return std::acos(Normalize().Dot(vector.Normalize()));
    }



    // ====Operator overloads====

    Vector3& Vector3::operator+=(const Vector3& vector)
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
        return *this;
    }

    Vector3 Vector3::operator+(const Vector3& vector) const
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

    Vector3 Vector3::operator-(const Vector3& vector) const
    {
        return Vector3(*this) -= vector;
    }

    Vector3 Vector3::operator*(const Vector3& vector) const
    {
        return Vector3(X * vector.X, Y * vector.Y, Z * vector.Z);
    }

    Vector3 Vector3::operator*(float scalar) const
    {
        return Vector3(X * scalar, Y * scalar, Z * scalar);
    }

    Vector3 Vector3::operator/(const Vector3& vector) const
    {
        return Vector3(X / vector.X, Y / vector.Y, Z / vector.Z);
    }

    Vector3 Vector3::operator/(float scalar) const
    {
        return Vector3(X / scalar, Y / scalar, Z / scalar);
    }

    Vector3 Vector3::operator-() const
    {
        return Vector3(-X, -Y, -Z);
    }

    bool Vector3::operator==(const Vector3& vector) const
    {
        return (X == vector.X) && (Y == vector.Y) && (Z == vector.Z);
    }

    bool Vector3::operator!=(const Vector3& vector) const
    {
        return (X != vector.X) || (Y != vector.Y) || (Z != vector.Z);
    }

    std::string Vector3::ToString() const
    {
        return fmt::format("({}, {}, {})", std::round(X * 1000) / 1000, std::round(Y * 1000) / 1000, std::round(Z * 1000) / 1000);
    }

    Vector3 operator*(float scalar, const Vector3& vector)
    {
        return Vector3(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
    }
}