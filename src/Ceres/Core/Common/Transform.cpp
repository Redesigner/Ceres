#include "Transform.h"

namespace Ceres
{
    Transform::Transform()
        :_matrix(Matrix::Identity()), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
    {}

    Transform::~Transform()
    {}


    void Transform::SetPosition(Vector3 position)
    {
        _position = position;
        calculateMatrix();
    }
    const Vector3& Transform::GetPosition()
    {
        return _position;
    }


    void Transform::SetRotation(Vector3 rotation)
    {
        _rotation = rotation;
        calculateMatrix();
    }
    const Vector3& Transform::GetRotation()
    {
        return _rotation;
    }


    void Transform::SetScale(Vector3 scale)
    {
        _scale = scale;
        calculateMatrix();
    }
    const Vector3& Transform::GetScale()
    {
        return _scale;
    }

    const Matrix& Transform::GetMatrix() const
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