#include "VertexPositionNormalLayout.h"

extern "C" 
{
	#include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}


namespace Ceres
{
    void VertexPositionNormalLayout::SetAttributes() const
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<void*>(sizeof(float) * 3));
    }
    int VertexPositionNormalLayout::Size() const
    {
        return sizeof(float) * 6;
    }
}