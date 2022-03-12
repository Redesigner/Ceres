#include "VertexPositionTextureLayout.h"

#include "../../Common/Vector2.h"

extern "C" 
{
	#include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}


namespace Ceres
{
    void VertexPositionTextureLayout::SetAttributes() const
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, Size(), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Size(), reinterpret_cast<void*>(sizeof(Vector2)));
    }
    int VertexPositionTextureLayout::Size() const
    {
        return sizeof(Vector2) * 2;
    }

    VertexPositionTextureLayout& VertexPositionTextureLayout::Get()
    {
        static VertexPositionTextureLayout layout;
        return layout;
    }
}