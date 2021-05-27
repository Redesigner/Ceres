#include "GraphicsDevice.h"

#include "Context.h"
#include "Effect.h"

#include <stdexcept>
#include <fmt/core.h>

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
        _window = createWindow();
        _currentContext = new Context(_window);
        _screenSurface = nullptr;
        _currentEffect = new Effect("Shaders\\defaultVertex.GLSL", "Shaders\\defaultFragment.GLSL");
    }

    GraphicsDevice::~GraphicsDevice()
    {
        delete _currentEffect;
        delete _currentContext;
        if(_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
        for (int i = 0; i < _vertexCollections.size(); i++)
        {
            delete _vertexCollections[i];
        }
    }

    void GraphicsDevice::Render()
    {
        beginRender();
        for (int i = 0; i < _vertexCollections.size(); i++)
        {
            _vertexCollections[i]->Render();
        }
        endRender();
    }

    void GraphicsDevice::beginRender()
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        _currentEffect->Begin();
    }

    void GraphicsDevice::endRender()
    {

        SDL_GL_SwapWindow(_window);
        printError();
    }

    void GraphicsDevice::printError()
    {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            fmt::print("OpenGL error: {}\n", gluErrorString(err));
        }
    }

    SDL_Window* GraphicsDevice::createWindow()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) { return false; }
        return SDL_CreateWindow("Ceres",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    }
}