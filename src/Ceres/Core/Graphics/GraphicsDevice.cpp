#include "GraphicsDevice.h"

#include "Context.h"
#include "Effect.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

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
        _currentVAO = new VertexArrayObject();
        _currentVBO = new VertexBufferObject(32);
        _currentVAO->Bind(_currentVBO);
    }
    GraphicsDevice::~GraphicsDevice()
    {
        delete _currentVAO;
        delete _currentVBO;
        delete _currentEffect;
        delete _currentContext;
        if(_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
    }

    void GraphicsDevice::LoadVertices(std::vector<Vector3> vertices)
    {
        _currentVBO->SetData(vertices);
        printError();
        fmt::print("Adding {} vertices to VBO.\n", vertices.size());
    }

    void GraphicsDevice::Render()
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        _currentEffect->Begin();
        _currentVBO->Bind();
        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
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