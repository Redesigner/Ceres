#include "Matrix.h"

#include <cmath>
#include <fmt/core.h>

namespace Ceres
{
    Matrix::Matrix(
        float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44)
        : M{{m11, m21, m31, m41}, {m12, m22, m32, m42}, {m13, m23, m33, m43}, {m14, m24, m34, m44}}
    {}

    Matrix::Matrix()
        : M{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}
    {}

    Matrix::~Matrix()
    {}

    Matrix Matrix::Translation(float x, float y, float z)
    {
        return Matrix(
            1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1
        );
    }

    Matrix Matrix::RotationAlongX(float angle)
    {
        float cos = std::cos(angle);
        float sin = std::sin(angle);
        return Matrix(
            1, 0, 0, 0,
            0, cos, sin, 0,
            0, -sin, cos, 0,
            0, 0, 0, 1
        );
    }

    Matrix Matrix::RotationAlongY(float angle)
    {
        float cos = std::cos(angle);
        float sin = std::sin(angle);
        return Matrix(
            cos, 0, -sin, 0,
            0, 1, 0, 0,
            sin, 0, cos, 0,
            0, 0, 0, 1
        );
    }

    Matrix Matrix::RotationAlongZ(float angle)
    {
        float cos = std::cos(angle);
        float sin = std::sin(angle);
        return Matrix(
            cos, sin, 0, 0,
            -sin, cos, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }

    Matrix Matrix::RotationFromEuler(float roll, float pitch, float yaw)
    {
        float cosA = std::cos(roll);
        float sinA = std::sin(roll);
        
        float cosB = std::cos(pitch);
        float sinB = std::sin(pitch);

        float cosR = std::cos(yaw);
        float sinR = std::sin(yaw);

        return Matrix(
            (cosA * cosB), (cosA * sinB * sinR) - (sinA * cosR), (cosA * sinB * cosR) + (sinA * sinR), 0,
            (sinA * cosB), (sinA * sinB * sinR) + (cosA * cosR), (sinA * sinB * cosR) - (cosA * sinR), 0,
            -sinB, (cosB * sinR), (cosB * cosR), 0,
            0, 0, 0, 1
        );
    }

    Matrix Matrix::TranslationScale(float xPos, float yPos, float zPos, float xScale, float yScale, float zScale)
    {
        return Matrix(
            xScale, 0, 0, xPos,
            0, yScale, 0, yPos,
            0, 0, zScale, zPos,
            0, 0, 0, 1
        );
    }

    Matrix Matrix::Scale(float x, float y, float z)
    {
        return Matrix(
          x, 0, 0, 0,
          0, y, 0, 0,
          0, 0, z, 0,
          0, 0, 0, 1
        );
    }

    Matrix Matrix::Identity()
    {
        return Matrix(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }

    Matrix Matrix::Zero()
    {
        return Matrix(
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
        );
    }

    Matrix Matrix::Perspective(float width, float height, float fOV, float near, float far)
    {
        float rFOV = fOV / 180 * (float) std::acos(0);
        float ratio = width / height;
        float t = std::tan(rFOV / 2) * near;
        float b = -t;
        float r = t * ratio;
        float l = (-t) * ratio;

        return Matrix(
            ((2 * near) / (r - l)),     0,                      0,                                  0,
            0,                          ((2 * near) / (t - b)), 0,                                  0,
            ((r + l) / (r - l)),        ((t + b) / (t - b)),    -((far + near) / (far - near)),     ((-2 * near * far) / (far - near)),
            0,                          0,                      -1,                                 0
        );
    }

    Matrix Matrix::LookAt(const Vector3& eyePos, const Vector3& targetPos, const Vector3& up)
    {
        Vector3 zAxis = (eyePos - targetPos).Normalize();
        Vector3 xAxis = up.Cross(zAxis).Normalize();
        Vector3 yAxis = zAxis.Cross(xAxis);

        return Matrix(
            xAxis.X, xAxis.Y, xAxis.Z, -xAxis.Dot(eyePos),
            yAxis.X, yAxis.Y, yAxis.Z, -yAxis.Dot(eyePos),
            zAxis.X, zAxis.Y, zAxis.Z, -zAxis.Dot(eyePos),
            0, 0, 0, 1
        );
    }

    std::string Matrix::ToString() const
    {
        std::string result = "M:\n";
        for(int i = 0; i < 4; i++)
        {
            result += fmt::format("{}, {}, {}, {}\n",
                M[i][0], M[i][1], M[i][2], M[i][3]);
        }
        return result;
    }


    Matrix Matrix::operator*(const Matrix& b)
    {
        Matrix result = Zero();
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                result.M[i][j] =
                (this->M[i][0] * b.M[0][j]) +
                (this->M[i][1] * b.M[1][j]) + 
                (this->M[i][2] * b.M[2][j]) +
                (this->M[i][3] * b.M[3][j]);
            }
        }
        return result;
    }

    Matrix::operator float *()
    {
        return M[0];
    }
}
