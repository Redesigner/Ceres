#pragma once

#include "../Common/Vector3.h"
#include "VertexTypes/IVertexType.h"
#include "VertexTypes/IVertexLayout.h"

#include <fmt/core.h>
#include <vector>
#include <stdexcept>

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
            VertexBufferObject(int capacity, const IVertexLayout& vertexLayout);
            ~VertexBufferObject();

            void SetData(const IVertexType data[], const int size, const int offset);
            void SetData(const IVertexType data[], const int size);            

            void Bind();

        private:
            int _capacity;
            int _currentIndex;
            int _size;
            GLuint _gVBO;
    };
}