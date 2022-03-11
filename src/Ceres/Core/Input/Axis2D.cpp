#include "Axis2D.h"

namespace Ceres
{
    Axis2DKey::Axis2DKey(Button up, Button down, Button left, Button right)
        :_up(up), _left(left), _down(down), _right(right)
    {}

    Vector2 Axis2DKey::GetValue() const
    {
        float x = 0;
        float y = 0;

        if(buttonPressed(_up))
        {
            y++;
        }
        if(buttonPressed(_down))
        {
            y--;
        }
        if(buttonPressed(_left))
        {
            x--;
        }
        if(buttonPressed(_right))
        {
            x++;
        }
        return Vector2(x, y).Normalize();
    }

    bool Axis2DKey::buttonPressed(Button button) const
    {
        if(button <= Button::Gamepad_invalid)
        {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            return state[static_cast<int>(button)] == 1;
        }
        return false;
    }

    Axis2DJoy::Axis2DJoy(std::vector<Joystick>& controllerContainer, int playerIndex, int axisX, int axisY)
        :_controllerContainer(controllerContainer), _playerIndex(playerIndex), _axisX(axisX), _axisY(axisY)
    {}

    Vector2 Axis2DJoy::GetValue() const
    {
        if (_controllerContainer.size() > _playerIndex)
        {
            Joystick& controller = _controllerContainer.at(_playerIndex);
            Vector2 result = Vector2(controller.GetAxisValue(_axisX), controller.GetAxisValue(_axisY));
            if (result.LengthSquared() > 1.0f)
            {
                result = result.Normalize();
            }
            return result;
        }
        return Vector2(0.0f, 0.0f);
    }
}