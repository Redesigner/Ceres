#pragma once

#include "Buttons.h"

#include <functional>
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
        private:
            std::unordered_map<Button, voidFunctionType> _map;
    };
}