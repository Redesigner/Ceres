#include "GraphicsDevice.h"
extern "C" 
{
	#include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

namespace Ceres
{
    GraphicsDevice::GraphicsDevice()
    {
        _window = nullptr;
        screenSurface = nullptr;
    }
    GraphicsDevice::~GraphicsDevice()
    {
        if(_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
    }

    bool GraphicsDevice::CreateWindow()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) { return false; }
        _window = SDL_CreateWindow("Ceres",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(_window == nullptr) { return false; }

        screenSurface = SDL_GetWindowSurface(_window);
        return true;
    }
}