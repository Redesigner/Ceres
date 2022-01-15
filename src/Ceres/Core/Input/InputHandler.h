#pragma once

#include "Axis.h"
#include "Axis2D.h"
#include "Buttons.h"
#include "../Common/Vector2.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <forward_list>

extern "C"
{
    #include <SDL2/SDL.h>
}

typedef void (*voidFunctionType)(void);
using cursorFunctionType = std::function<void(int, int)>;

namespace Ceres
{
    class InputHandler
    {
        public:
            InputHandler();
            ~InputHandler();

            void HandleInput(Button input);
            void HandleCursorInput(int x, int y);

            void BindInput(Button input, voidFunctionType function);
            void BindCursorInput(cursorFunctionType& function);

            void BindAxis(std::string id, Button positive, Button negative);
            float GetAxisValue(std::string id) const;

            void BindAxis2D(std::string id, Button up, Button down, Button left, Button right);
            Vector2 GetAxis2DValue(std::string id) const;

        private:
            bool buttonPressed(Button button) const;
            std::unordered_map<Button, voidFunctionType> _inputMap;
            std::forward_list<cursorFunctionType> _cursorInputMap;
            std::unordered_map<std::string, Axis> _axisMap;
            std::unordered_map<std::string, Axis2D> _axis2DMap;
    };
}