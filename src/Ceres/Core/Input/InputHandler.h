#pragma once

#include "Axis.h"
#include "Axis2D.h"
#include "Buttons.h"
#include "Joystick.h"
#include "../Common/Vector2.h"

#include <functional>
#include <string>
#include <map>
#include <unordered_map>
#include <forward_list>

extern "C"
{
    #include <SDL2/SDL.h>
}

using voidFunctionType = std::function<void(void)>;
using cursorFunctionType = std::function<void(int, int)>;

namespace Ceres
{
    class InputHandler
    {
        public:
            InputHandler();
            ~InputHandler();

            void RegisterController(int deviceIndex);

            void HandleInput(Button input);
            void HandleCursorInput(int x, int y);

            void BindInput(Button input, std::string actionName);
            void BindAction(std::string actionName, voidFunctionType function);
            void BindCursorInput(cursorFunctionType& function);

            void BindAxis(std::string id, Button positive, Button negative);
            float GetAxisValue(std::string id) const;

            void BindAxis2D(std::string id, Button up, Button down, Button left, Button right);
            void BindAxis2D(std::string id, int playerIndex, int axisX, int axisY);
            Vector2 GetAxis2DValue(std::string id) const;

            bool ButtonPressed(Button button) const;

        private:
            std::vector<Joystick> _controllers;
            std::unordered_map<Button, std::string> _inputMap;
            std::unordered_map<std::string, voidFunctionType> _actionMap;
            std::forward_list<cursorFunctionType> _cursorInputMap;
            std::unordered_map<std::string, Axis> _axisMap;
            std::multimap<std::string, Axis2D*> _axis2DMap;
    };
}