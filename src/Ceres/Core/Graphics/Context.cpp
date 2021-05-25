#include "Context.h"

#include "Effect.h"

#include <fmt/core.h>

extern "C"
{
	#include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
    #include <gl/GLU.h>
}

namespace Ceres
{
    Context::Context(SDL_Window* window)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        _glContext = SDL_GL_CreateContext(window);
        GLenum glewError = glewInit();

        fmt::print("Initializing GLEW... {}\n", glewGetErrorString(glewError));
        
        Effect* defaultEffect = new Effect("shaders/default.GLSL");
        defaultEffect->Attach(); 
    }
}