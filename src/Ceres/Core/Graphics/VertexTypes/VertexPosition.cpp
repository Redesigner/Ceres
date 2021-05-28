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
    {}
}