#include "GraphicsDevice.h"

#include "Context.h"

#include <stdexcept>

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
        _window = CreateWindow();
        _currentContext = CreateContext(_window);
        screenSurface = nullptr;
    }
    GraphicsDevice::~GraphicsDevice()
    {
        if(_currentContext != nullptr)
        {
            SDL_GL_DeleteContext(_currentContext);
        }
        if(_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
    }

    SDL_Window* GraphicsDevice::CreateWindow()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) { return false; }
        return SDL_CreateWindow("Ceres",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    }

    Context* GraphicsDevice::CreateContext(SDL_Window* window)
    {
        if(window != nullptr)
        {
            return new Context(window);
        }
        else
        {
            throw std::runtime_error("The OpenGL window is invalid or hasn't been created.");
        }
    }
}