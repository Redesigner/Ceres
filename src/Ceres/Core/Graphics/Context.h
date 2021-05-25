#pragma once

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

struct SDL_Window;
namespace Ceres
{
    class Context
    {
        public:
            Context::Context(SDL_Window* window);
            Context::~Context();
        private:
            SDL_GLContext _glContext;
    };
}