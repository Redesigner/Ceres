#pragma once

#include "Axis.h"
#include "Buttons.h"
#include "../Common/Vector2.h"

#include <functional>
#include <string>
#include <unordered_map>

extern "C"
{
    #include <SDL2/SDL.h>
}

typedef void (*voidFunctionType)(void); 
namespace Ceres
{
    class InputHandler
    {
        public:
            InputHandler();
            ~InputHandler();

            void HandleInput(Button input);
            void BindInput(Button input, voidFunctionType function);

            void BindAxis(std::string id, Button up, Button down, Button left, Button right);
            Vector2 GetAxisValue(std::string id);

        private:
            bool buttonPressed(Button button);
            std::unordered_map<Button, voidFunctionType> _map;
            std::unordered_map<std::string, Axis> _axisMap;
    };
}