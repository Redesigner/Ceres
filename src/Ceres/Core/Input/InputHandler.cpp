#include "InputHandler.h"

#include <fmt/core.h>

const int MAX_INPUTMAP_SIZE = 32;
const int MAX_AXIS_SIZE = 2;
namespace Ceres
{
    InputHandler::InputHandler()
        :_inputMap(std::unordered_map<Button, std::string>()),
        _actionMap(std::unordered_map<std::string, voidFunctionType>()),
        _axis2DMap(std::multimap<std::string, Axis2D*>())
    {
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
        if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
        {
            fmt::print("[input] Unable to initialize sdl gamecontroller subsystem.\n");
            return;
        }
        SDL_JoystickEventState(SDL_ENABLE);
    }

    InputHandler::~InputHandler()
    {
        _controllers.clear();
        for (std::pair<std::string, Axis2D*> binding : _axis2DMap)
        {
            delete binding.second;
        }
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    }

    void InputHandler::RegisterController(int deviceIndex)
    {
        _controllers.emplace_back(deviceIndex);
    }

    void InputHandler::BindInput(Button input, std::string actionName)
    {
        _inputMap.insert(std::pair<Button, std::string>(input, actionName));
    }

    void InputHandler::BindAction(std::string actionName, voidFunctionType function)
    {
        _actionMap.insert(std::pair<std::string, voidFunctionType>(actionName, function));
    }
    
    void InputHandler::BindCursorInput(cursorFunctionType& function)
    {
        _cursorInputMap.emplace_front(function);
    }


    void InputHandler::HandleInput(Button input)
    {
        std::unordered_map<Button, std::string>::const_iterator get = _inputMap.find(input);
        if (get == _inputMap.end())
        {
            return;
        }
        std::unordered_map<std::string, voidFunctionType>::const_iterator action = _actionMap.find(get->second);
        if (action == _actionMap.end())
        {
            return;
        }
        action->second();
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
        if(ButtonPressed(axis.Positive))
        {
            x++;
        }
        if(ButtonPressed(axis.Negative))
        {
            x--;
        }
        return x;
    }


    void InputHandler::BindAxis2D(std::string id, Button up, Button down, Button left, Button right)
    {
        Axis2D* axis2D = new Axis2DKey(up, down, left, right);
        _axis2DMap.insert(std::pair<std::string, Axis2D*>(id, axis2D));
    }

    void InputHandler::BindAxis2D(std::string id, int playerIndex, int axisX, int axisY)
    {
        Axis2D* axis2D = new Axis2DJoy(_controllers, playerIndex, axisX, axisY);
        _axis2DMap.insert(std::pair<std::string, Axis2D*>(id, axis2D));
    }


    Vector2 InputHandler::GetAxis2DValue(std::string id) const
    {
        auto get = _axis2DMap.equal_range(id);
        if(get.first == get.second)
        {
            fmt::print("Unable to find axis {}\n", id);
            return Vector2(0.0f, 0.0f);
        }
        float longestAxis = 0.0f;
        Vector2 result = Vector2(0.0f, 0.0f);
        for (auto iter = get.first; iter != get.second; ++iter)
        {
            Vector2 current = iter->second->GetValue();
            float currentLength = current.LengthSquared();
            if (currentLength > longestAxis)
            {
                longestAxis = currentLength;
                result = current;
            }
        }
        return result;
    }


    bool InputHandler::ButtonPressed(Button button) const
    {
        // Is a keyboard button
        if(button <= Button::Gamepad_invalid)
        {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            // define safer conversion?
            return state[static_cast<int>(button)] == 1;
        }
        return false;
    }
}