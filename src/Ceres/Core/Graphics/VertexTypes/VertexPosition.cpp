#include "VertexPosition.h"

#include <fmt/core.h>

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    VertexPosition::VertexPosition(Vector3 position)
        : Position(position){}
    VertexPosition::~VertexPosition()
    {
        
    }

    void VertexPosition::SetAttributes()
    {
        fmt::print("Attempting to bind VertexPosition.\nSize is {}", sizeof(VertexPosition));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

}