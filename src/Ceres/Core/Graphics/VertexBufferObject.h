#pragma once

#include "../Vector3.h"

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

            void SetData(std::vector<Vector3> data, unsigned int offset);
            void SetData(std::vector<Vector3> data);
        private:
            unsigned int _capacity;
            unsigned int _currentIndex;
            GLuint _gVBO;
    };
}