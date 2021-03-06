#include "Window.h"

#pragma warning(push, 0)
extern "C"
{
    #include <SDL2/SDL.h>
    #include "SDL_image.h"
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}
#pragma warning(pop)

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
        const int multisampleSampleCount = 8;
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, multisampleBufferCount);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisampleSampleCount);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        _sdlWindow = SDL_CreateWindow("Ceres",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        Lock();
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

    void Window::Lock()
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    void Window::Unlock()
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }

    void Window::Resize(const int width, const int height)
    {
        glViewport(0, 0, width, height);
        SDL_SetWindowSize(_sdlWindow, width, height);
        _width = width;
        _height = height;
        _restoreWidth = width;
        _restoreHeight = height;
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
            _width = displayMode.w;
            _height = displayMode.h;
        }
        else
        {
            SDL_SetWindowFullscreen(_sdlWindow, false);
            glViewport(0, 0, _restoreWidth, _restoreHeight);
            SDL_SetWindowSize(_sdlWindow, _restoreWidth, _restoreHeight);
            _width = _restoreWidth;
            _height = _restoreHeight;
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

    Vector2 Window::GetViewportSize() const
    {
        // There really shouldn't be any loss of precision here, unless the viewport size is something outrageous
        return Vector2(_width, _height);
    }
}