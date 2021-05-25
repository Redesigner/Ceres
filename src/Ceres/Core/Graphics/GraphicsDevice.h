#pragma once

struct SDL_Window;
struct SDL_Surface;

namespace Ceres
{
    class Context;
    class GraphicsDevice
    {
        public:

            GraphicsDevice();
            ~GraphicsDevice();

            SDL_Window* CreateWindow();
            Context* CreateContext(SDL_Window* window);
            
        private:
            SDL_Window* _window;
            SDL_Surface* screenSurface;

            Context* _currentContext;
    };
}