#pragma once

#include <functional>
#include <unordered_map>

extern "C"
{
    #include <SDL2/SDL.h>
}

namespace Ceres
{
    class InputHandler
    {
        public:
            InputHandler();
            ~InputHandler();
        private:
            // std::unordered_map<unsigned int, std::function<void>> _map;
    };
}