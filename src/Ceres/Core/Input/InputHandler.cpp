#include "InputHandler.h"

#include <fmt/core.h>

const int MAX_INPUTMAP_SIZE = 32;
const int MAX_AXIS_SIZE = 2;
namespace Ceres
{
    InputHandler::InputHandler()
        :_inputMap(std::unordered_map<Button, voidFunctionType>(MAX_INPUTMAP_SIZE)),
        _axis2DMap(std::unordered_map<std::string, Axis2D>(MAX_AXIS_SIZE))
    {}

    InputHandler::~InputHandler()
    {}

    void InputHandler::BindInput(Button input, voidFunctionType function)
    {
        _inputMap.insert(std::pair<Button, voidFunctionType>(input, function));
    }
    
    void InputHandler::BindCursorInput(cursorFunctionType& function)
    {
        _cursorInputMap.emplace_front(function);
    }


    void InputHandler::HandleInput(Button input)
    {
        std::unordered_map<Button, voidFunctionType>::const_iterator get = _inputMap.find(input);
        if(get == _inputMap.end())
        {
            return;
        }
        get->second();
    }

    void InputHandler::HandleCursorInput(int x, int y)
    {
        for (cursorFunctionType function : _cursorInputMap)
        {
            function(x, y);
        }
    }


    // ============ State-based axis logic =============

    void InputHandler::BindAxis(std::string id, Button positive, Button negative)
    {
        _axisMap.insert(std::pair<std::string, Axis>(id, Axis(positive, negative)));
    }

    float InputHandler::GetAxisValue(std::string id) const
    {
        std::unordered_map<std::string, Axis>::const_iterator get = _axisMap.find(id);
        if(get == _axisMap.end())
        {
            fmt::print("Unable to find axis {}\n", id);
            return 0;
        }

        Axis axis = get->second;

        float x = 0;
        if(buttonPressed(axis.Positive))
        {
            x++;
        }
        if(buttonPressed(axis.Negative))
        {
            x--;
        }
        return x;
    }


    void InputHandler::BindAxis2D(std::string id, Button up, Button down, Button left, Button right)
    {
        _axis2DMap.insert(std::pair<std::string, Axis2D>(id, Axis2D(up, down, left, right)));
    }

    Vector2 InputHandler::GetAxis2DValue(std::string id) const
    {
        std::unordered_map<std::string, Axis2D>::const_iterator get = _axis2DMap.find(id);
        if(get == _axis2DMap.end())
        {
            fmt::print("Unable to find axis {}\n", id);
            return Vector2(0, 0);
        }

        Axis2D axis = get->second;

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