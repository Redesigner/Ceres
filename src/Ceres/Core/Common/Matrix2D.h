#pragma once

#include "Vector2.h"

namespace Ceres
{
	struct Matrix2D
	{
		public:
			Matrix2D(
				float m11, float m12, float m13,
				float m21, float m22, float m23,
				float m31, float m32, float m33
			);
			Matrix2D();
			~Matrix2D();

			static Matrix2D Translation(float x, float y);
			static Matrix2D Rotation(float theta);
			static Matrix2D Scale(float x, float y);

			static Matrix2D Sprite(float x, float y, float w, float h, float screenW, float screenH);

			static Matrix2D Zero();

			Matrix2D operator*(const Matrix2D& b);
			Vector2 operator*(const Vector2& b);

			operator float*();

			float M[3][3];
	}; 
}