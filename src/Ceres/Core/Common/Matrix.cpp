#include "Matrix.h"

namespace Ceres
{
    Matrix::Matrix(
        float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44)
    {
        M[0][0] = m11;
        M[0][1] = m12;
        M[0][2] = m13;
        M[0][3] = m14;
        M[1][0] = m21;
        M[1][1] = m22;
        M[1][2] = m23;
        M[1][3] = m24;
        M[2][0] = m31;
        M[2][1] = m32;
        M[2][2] = m33;
        M[2][3] = m34;
        M[3][0] = m41;
        M[3][1] = m42;
        M[3][2] = m43;
        M[3][3] = m44;
    }

    Matrix Matrix::Identity()
    {
        return Matrix(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    }

    Matrix Matrix::Zero()
    {
        return Matrix(
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0);
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
}
