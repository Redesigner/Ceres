#include "VertexPositionNormalColorLayout.h"

#include "../../Common/Vector3.h"
#include "../../Common/Color.h"

extern "C" 
{
	#include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}


namespace Ceres
{
    void VertexPositionNormalColorLayout::SetAttributes() const
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Size(), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Size(), reinterpret_cast<void*>(sizeof(Vector3)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, GL_BGRA, GL_UNSIGNED_BYTE, GL_TRUE, Size(), reinterpret_cast<void*>(sizeof(Vector3) * 2));
    }
    int VertexPositionNormalColorLayout::Size() const
    {
        return sizeof(Vector3) * 2 + sizeof(Color);
    }
}