#pragma once

#include "../Common/Vector3.h"

#include <vector>

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    class VertexBufferObject
    {
        public:
            VertexBufferObject(unsigned int vertexCount);
            ~VertexBufferObject();

            void SetData(Vector3 data[], unsigned int size, unsigned int offset);
            void SetData(Vector3 data[], unsigned int size);

            void Bind();
        private:
            unsigned int _capacity;
            unsigned int _currentIndex;
            GLuint _gVBO;
    };
}