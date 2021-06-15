#include "InputHandler.h"

#include <fmt/core.h>

const int MAX_INPUTMAP_SIZE = 32;
const int MAX_AXIS_SIZE = 2;
namespace Ceres
{
    InputHandler::InputHandler()
        :_map(std::unordered_map<Button, voidFunctionType>(MAX_INPUTMAP_SIZE)),
        _axisMap(std::unordered_map<std::string, Axis>(MAX_AXIS_SIZE))
    {}

    InputHandler::~InputHandler()
    {}

    void InputHandler::BindInput(Button input, voidFunctionType function)
    {
        _map.insert(std::pair<Button, voidFunctionType>(input, function));
    }

    void InputHandler::HandleInput(Button input)
    {
        std::unordered_map<Button, voidFunctionType>::const_iterator get = _map.find(input);
        if(get == _map.end())
        {
            return;
        }
        get->second();
    }

    void InputHandler::BindAxis(std::string id, Button up, Button down, Button left, Button right)
    {
        _axisMap.insert(std::pair<std::string, Axis>(id, Axis(up, down, left, right)));
    }

    Vector2 InputHandler::GetAxisValue(std::string id) const
    {
        std::unordered_map<std::string, Axis>::const_iterator get = _axisMap.find(id);
        if(get == _axisMap.end())
        {
            fmt::print("Unable to find axis {}", id);
            return Vector2(0, 0);
        }

        Axis axis = get->second;

        float x = 0;
        float y = 0;

        if(buttonPressed(axis.Up))
        {
            y++;
        }
        if(buttonPressed(axis.Down))
        {
            y--;
        }
        if(buttonPressed(axis.Left))
        {
            x--;
        }
        if(buttonPressed(axis.Right))
        {
            x++;
        }
        return Vector2(x, y).Normalize();

    }

    bool InputHandler::buttonPressed(Button button) const
    {
        // Is a keyboard button
        if(button <= Button::Gamepad_invalid)
        {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            // define safer conversion?
            return state[(int) button] == 1;
        }
        return false;
    }
}