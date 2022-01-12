#include "VertexPositionLayout.h"

#include <fmt/core.h>

extern "C" 
{
	#include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}


namespace Ceres
{
    void VertexPositionLayout::SetAttributes() const
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
    int VertexPositionLayout::Size() const
    {
        return sizeof(float) * 3;
    }
}