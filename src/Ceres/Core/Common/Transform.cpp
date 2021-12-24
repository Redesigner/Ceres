#include "Transform.h"

#include <fmt/core.h>

namespace Ceres
{
    Transform::Transform()
        :_matrix(Matrix::Identity()),
        _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
    {
        _positionMatrix = Matrix::Translation(_position.X, _position.Y, _position.Z);
        _rotationMatrix = Matrix::RotationFromEuler(_rotation.X, _rotation.Y, _rotation.Z);
        _scaleMatrix = Matrix::Scale(_scale.X, _scale.Y, _scale.Z);
        calculateMatrix();
    }

    Transform::~Transform()
    {}


    void Transform::SetPosition(const Vector3& position)
    {
        _position = position;
        _positionMatrix = Matrix::Translation(_position.X, _position.Y, _position.Z);
        calculateMatrix();
    }
    Vector3 Transform::GetPosition() const
    {
        return _position;
    }
    Matrix Transform::GetPositionMatrix() const
    {
        return _positionMatrix;
    }

    void Transform::SetRotation(const Vector3& rotation)
    {
        _rotation = rotation;
        _rotationMatrix = Matrix::RotationFromEuler(_rotation.X, _rotation.Y, _rotation.Z);
        calculateMatrix();
    }
    Vector3 Transform::GetRotation() const
    {
        return _rotation;
    }
    Matrix Transform::GetRotationMatrix() const
    {
        return _rotationMatrix;
    }


    void Transform::SetScale(const Vector3& scale)
    {
        _scale = scale;
        _scaleMatrix = Matrix::Scale(_scale.X, _scale.Y, _scale.Z);
        calculateMatrix();
    }
    Vector3 Transform::GetScale() const
    {
        return _scale;
    }
    Matrix Transform::GetScaleMatrix() const
    {
        return _scaleMatrix;
    }


    Matrix Transform::GetMatrix() const
    {
        return _matrix;
    }

    Matrix Transform::GetInverse() const
    {
        return
        Matrix::Translation(-_position.X, -_position.Y, -_position.Z) *
        Matrix::Scale(1 / _scale.X, 1 / _scale.Y, 1 / _scale.Z) *
        _rotationMatrix.Transpose();
    }


    void Transform::calculateMatrix()
    {
        _matrix =
        _rotationMatrix *
        _scaleMatrix * 
        _positionMatrix;
    }
}