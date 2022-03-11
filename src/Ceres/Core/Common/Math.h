#pragma once

#include <cmath>

namespace Ceres
{
	class Math
	{
		public:
			constexpr static float Pi()
			{
				return 3.141592f;
			}
			constexpr static float Tau()
			{
				return 1.570796f;
			}

			constexpr static float DegreesToRadians(const float x)
			{
				return x / 180.0f * Pi();
			}

			/// Clamps a value to an equivalent angle from [-pi/2, pi/2]
			static float ClampRadians(float x)
			{
				// Only use fmod if x is outside of [-pi, pi], otherwise a single addition/subtraction is much faster
				if (x > Pi() || x < -Pi())
				{
					x = std::fmodf(x, 2 * Pi());
				}
				if (x > Pi())
				{
					return x - 2 * Pi();
				}
				if (x < -Pi())
				{
					return x + 2 * Pi();
				}
				return x;
			}
	};
}