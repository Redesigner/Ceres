#include "Joystick.h"

#include <fmt/core.h>

namespace Ceres
{
	Joystick::Joystick(int deviceIndex)
	{
		SDL_Joystick* joystick = SDL_JoystickOpen(deviceIndex);
		if (joystick == nullptr)
		{
			return;
		}
		_joystick = joystick;
	};

	Joystick::Joystick(Joystick&& joystick)
	{
		joystick._initialized = false;
		_joystick = joystick._joystick;
	}

	Joystick::~Joystick()
	{
		if (_initialized && SDL_JoystickGetAttached(_joystick))
		{
			SDL_JoystickClose(_joystick);
		}
	}

	float Joystick::GetAxisValue(int index) const
	{
		// Negative indices for joystick axes aren't possible,
		// so a negative index value just indicates the axis at the positive index, but inverted
		int realIndex = index;
		if (index < 0)
		{
			realIndex = -index;
		}
		float value = SDL_JoystickGetAxis(_joystick, realIndex);
		if (value < 0)
		{
			value /= 32768.0f;
		}
		else if (value > 0)
		{
			value /= 32767.0f;
		}
		if (index < 0)
		{
			value = -value;
		}
		if (std::abs(value) < _deadZone)
		{
			value = 0.0f;
		}
		return value;
	}

	bool Joystick::GetButtonPressed(int index) const
	{
		return SDL_JoystickGetButton(_joystick, index) == 1;
	}
}