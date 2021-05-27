#pragma once

#include "IndexBuffer.h"
#include "VertexBufferObject.h"

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    template <typename V>
    class VertexArrayObject
    {
        public:
            VertexArrayObject()
            {
                _gVAO = 0;
                glGenVertexArrays(1, &_gVAO);
                glBindVertexArray(_gVAO);
            }
            ~VertexArrayObject()
            {
                glDeleteVertexArrays(1, &_gVAO);
            }

            void Bind()
            {
                glBindVertexArray(_gVAO);
            }

            void BindTo(VertexBufferObject<V>* vBO)
            {
                glBindVertexArray(_gVAO);
                vBO->Bind();
            }

            void BindTo(IndexBuffer* iBO)
            {
                glBindVertexArray(_gVAO);
                iBO->Bind();
            }

        private:
            GLuint _gVAO;
    };
}