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
    class VertexBufferObject;

    class Context
    {
        public:
            Context(SDL_Window* window);
            ~Context();

        private:
            SDL_GLContext _glContext;
    };
}