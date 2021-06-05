#include "Transform.h"

#include <fmt/core.h>

namespace Ceres
{
    Transform::Transform()
        :_matrix(Matrix::Identity()), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
    {
        calculateMatrix();
    }

    Transform::~Transform()
    {}


    void Transform::SetPosition(const Vector3& position)
    {
        _position = position;
        calculateMatrix();
    }
    Vector3 Transform::GetPosition() const
    {
        return _position;
    }


    void Transform::SetRotation(const Vector3& rotation)
    {
        _rotation = rotation;
        calculateMatrix();
    }
    Vector3 Transform::GetRotation() const
    {
        return _rotation;
    }


    void Transform::SetScale(const Vector3& scale)
    {
        _scale = scale;
        calculateMatrix();
    }
    Vector3 Transform::GetScale() const
    {
        return _scale;
    }

    Matrix Transform::GetMatrix() const
    {
        return _matrix;
    }


    void Transform::calculateMatrix()
    {
        _matrix =
        Matrix::Translation(_position.X, _position.Y, _position.Z) *
        Matrix::Scale(_scale.X, _scale.Y, _scale.Z) *
        Matrix::RotationFromEuler(_rotation.X, _rotation.Y, _rotation.Z);
    }
}