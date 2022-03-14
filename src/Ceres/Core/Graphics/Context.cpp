#include "Context.h"

#include <fmt/core.h>
#include <fmt/color.h>

extern "C"
{
    #include <gl/GLU.h>
}

namespace Ceres
{
    Context::Context(const Window& window)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        const int multisampleBufferCount = 1;
        const int multisampleSampleCount = 16;
        
        _glContext = SDL_GL_CreateContext(window.Get());
        glewExperimental = true;
        GLenum glewError = glewInit();

        printPrefix();
        fmt::print("Initializing GLEW... {}\n", glewGetErrorString(glewError));

        if(SDL_GL_SetSwapInterval(1) != 0)
        {
            printPrefix();
            fmt::print("Failed to enable VSync. {}\n", glewGetErrorString(glewError));
        }

        int actualBufferCount = 0;
        int actualSampleCount = 0;
        SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &actualBufferCount);
        SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &actualSampleCount);

        if (actualBufferCount != multisampleBufferCount)
        {
            printPrefix();
            fmt::print("OpenGL attribute 'MultiSampleBuffers' was set to {}.\n", actualBufferCount);
        }
        if (actualSampleCount != multisampleSampleCount)
        {
            printPrefix();
            fmt::print("OpenGL attribute 'MultiSampleSamples' was set to {}.\n", actualSampleCount);
        }
    }

    Context::~Context()
    {
        SDL_GL_DeleteContext(_glContext);
    }

    void Context::printPrefix() const
    {
        fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "[GraphicsDevice] ");
    }
}