#include "VertexPositionNormal.h"

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    VertexPositionNormal::VertexPositionNormal(Vector3 vertex, Vector3 normal)
        : Vertex(vertex), Normal(normal){}

    VertexPositionNormal::VertexPositionNormal()
        : Vertex(Vector3(0)), Normal(Vector3(0))
        {}

    VertexPositionNormal::~VertexPositionNormal()
    {}
}
