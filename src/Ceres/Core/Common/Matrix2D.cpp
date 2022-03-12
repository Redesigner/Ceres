#include "Matrix2D.h"

#include <cmath>

namespace Ceres
{
	Matrix2D::Matrix2D(
		float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33)
		: M{{m11, m21, m31}, {m21, m22, m32}, {m13, m23, m33}}
	{}

	Matrix2D::Matrix2D()
		: M{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}
	{}

	Matrix2D::~Matrix2D()
	{}

	Matrix2D Matrix2D::Translation(float x, float y)
	{
		return Matrix2D(
			1, 0, x,
			0, 1, y,
			0, 0, 1
		);
	}

	Matrix2D Matrix2D::Rotation(float theta)
	{
		float sin = std::sinf(theta);
		float cos = std::cosf(theta);
		return Matrix2D(
			cos, sin, 0,
			-sin, cos, 0,
			0, 0, 1
		);
	}

	Matrix2D Matrix2D::Scale(float x, float y)
	{
		return Matrix2D(
			x, 0, 0,
			0, y, 0,
			0, 0, 1
		);
	}

	Matrix2D Matrix2D::Zero()
	{
		return Matrix2D(
			0, 0, 0,
			0, 0, 0,
			0, 0, 0
		);
	}

	Matrix2D Matrix2D::operator*(const Matrix2D& b)
	{
		Matrix2D result = Matrix2D::Zero();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				result.M[i][j] =
				(M[i][0] * b.M[0][j]) +
				(M[i][1] * b.M[1][j]) +
				(M[i][2] * b.M[2][j]);
			}
		}
		return result;
	}

	Vector2 Matrix2D::operator*(const Vector2& b)
	{
		return Vector2(
			b.X * M[0][0] + b.Y * M[1][0] + M[2][0],
			b.X * M[0][1] + b.Y * M[1][1] + M[2][1]
		);
	}

	Matrix2D::operator float *()
    {
        return M[0];
    }
}