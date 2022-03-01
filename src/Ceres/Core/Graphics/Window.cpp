#include "Window.h"

extern "C"
{
    #include <SDL2/SDL.h>
    #include "SDL_image.h"
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

#include <fmt/core.h>

namespace Ceres
{
    Window::Window()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            fmt::print("Failed to initialize SDL.\n");
            return;
        }
        if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            fmt::print("Failed to initialize SDL_image.\n");
            return;
        }
        const int multisampleBufferCount = 1;
        const int multisampleSampleCount = 4;
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, multisampleBufferCount);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisampleSampleCount);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        _sdlWindow = SDL_CreateWindow("Ceres",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    }

    Window::~Window()
    {
        if (_sdlWindow)
        {
            SDL_DestroyWindow(_sdlWindow);
        }
    }

    SDL_Window* Window::Get() const
    {
        return _sdlWindow;
    }

    void Window::Resize(const int width, const int height)
    {
        glViewport(0, 0, width, height);
        SDL_SetWindowSize(_sdlWindow, width, height);
        _width = width;
        _height = height;
        /* for (EffectPtr effect : _loadedEffects)
        {
            effect->SetFrustrum(Matrix::Perspective(w, h, 90, .1f, 100.f));
        } */
    }

    void Window::SwapBuffer() const
    {
        SDL_GL_SwapWindow(_sdlWindow);
    }

    void Window::ToggleFullscreen()
    {
        // Use the SDL window state rather than storing it here, just to prevent desync
        bool fullscreen = SDL_GetWindowFlags(_sdlWindow) & SDL_WINDOW_FULLSCREEN;
        if (!fullscreen)
        {
            int displayIndex = SDL_GetWindowDisplayIndex(_sdlWindow);
            SDL_DisplayMode displayMode;
            SDL_GetDesktopDisplayMode(displayIndex, &displayMode);
            SDL_SetWindowSize(_sdlWindow, displayMode.w, displayMode.h);
            glViewport(0, 0, displayMode.w, displayMode.h);
            SDL_SetWindowFullscreen(_sdlWindow, true);
        }
        else
        {
            SDL_SetWindowFullscreen(_sdlWindow, false);
            glViewport(0, 0, _width, _height);
            SDL_SetWindowSize(_sdlWindow, _width, _height);
        }
    }
    
    void Window::Maximize()
    {

    }

    void Window::ResizeViewport()
    {
        int width = 0;
        int height = 0;
        SDL_GetWindowSize(_sdlWindow, &width, &height);
        glViewport(0, 0, width, height);
    }
}