#pragma once

#include "Axis.h"
#include "Axis2D.h"
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

            void BindAxis(std::string id, Button positive, Button negative);
            float GetAxisValue(std::string id) const;

            void BindAxis2D(std::string id, Button up, Button down, Button left, Button right);
            Vector2 GetAxis2DValue(std::string id) const;

        private:
            bool buttonPressed(Button button) const;
            std::unordered_map<Button, voidFunctionType> _map;
            std::unordered_map<std::string, Axis> _axisMap;
            std::unordered_map<std::string, Axis2D> _axis2DMap;
    };
}