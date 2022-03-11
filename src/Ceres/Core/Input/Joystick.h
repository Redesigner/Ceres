#pragma once

extern "C"
{
	#include <SDL2/SDL.h>
}

namespace Ceres
{
	class Joystick
	{
		public:
			Joystick(int deviceIndex);
			Joystick(Joystick&) = delete;
			Joystick(Joystick&&);
			~Joystick();

			float GetAxisValue(int index) const;
			bool GetButtonPressed(int index) const;
		private:
			SDL_Joystick* _joystick = nullptr;
			bool _initialized = true;
			float _deadZone = 0.1f;
	};
}