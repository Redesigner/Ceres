#pragma once

#include "Vector2.h"

namespace Ceres
{
	/**
	 * @brief A 2D affine transformation matrix, represented internally as a 3x3 array of floats
	 * 
	 */
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
			static Matrix2D TranslateAndScale(float x, float y, float w, float h);

			/**
			 * @brief Transformation matrix for mapping a sprite from screen coordinates to OpenGL space
			 * 
			 * @param x Sprite X position
			 * @param y Sprite Y position
			 * @param w Sprite width
			 * @param h Sprite height
			 * @param screenW Destination screen width
			 * @param screenH Destination screen height
			 * @return Matrix2D 
			 */
			static Matrix2D Sprite(float x, float y, float w, float h, float screenW, float screenH);

			static Matrix2D Zero();

			Matrix2D operator*(const Matrix2D& b);
			Vector2 operator*(const Vector2& b);

			operator float*();

			float M[3][3];
	}; 
}