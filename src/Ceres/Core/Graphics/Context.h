#pragma once

#pragma warning(push, 0)        
extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}
#pragma warning(pop)

#include "Window.h"

namespace Ceres
{
    class Context
    {
        public:
            Context(const Window& window);
            ~Context();

        private:
            SDL_GLContext _glContext;
            void printPrefix() const;
    };
}