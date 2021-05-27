#pragma once

#include "../Common/Vector3.h"

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
    template <typename V>
    class VertexBufferObject
    {
        public:
            VertexBufferObject(unsigned int capacity)
            {
                _capacity = capacity;
                _currentIndex = 0;
                _gVBO = 0;

                glGenBuffers(1, &_gVBO);
                glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
                glBufferData(GL_ARRAY_BUFFER, _capacity * sizeof(V), NULL, GL_DYNAMIC_DRAW);
            }
            ~VertexBufferObject()
            {
                glDeleteBuffers(1, &_gVBO);
            }

            template <typename V>
            void SetData(V data[], unsigned int size, unsigned int offset)
            {
                fmt::print("Loading {} vertices.\n", size);
                if(offset + size > _capacity)
                {
                    throw std::out_of_range("VertexBufferObject data out of range.");
                }
                _currentIndex += size;
                glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
                glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(V) * size, data);
            }

            template <typename V>
            void SetData(V data[], unsigned int size)
            {
                SetData(data, size, _currentIndex);
            }

            void Bind()
            {
                glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
            }

        private:
            unsigned int _capacity;
            unsigned int _currentIndex;
            GLuint _gVBO;
    };
}