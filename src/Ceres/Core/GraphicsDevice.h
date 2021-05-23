#pragma once

struct SDL_Window;
struct SDL_Surface;

namespace Ceres
{
    class GraphicsDevice
    {
        public:

            GraphicsDevice();
            ~GraphicsDevice();

            bool CreateWindow();
            
        private:
            SDL_Window* _window;
            SDL_Surface* screenSurface;
    };
}