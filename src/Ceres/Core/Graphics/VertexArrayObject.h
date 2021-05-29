#pragma once

#include "VertexTypes/IVertexLayout.h"

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    class VertexArrayObject
    {
        public:
            VertexArrayObject(const IVertexLayout& vertexLayout);
            ~VertexArrayObject();            

            void Bind() const;
            void SetAttributes();

        private:
            GLuint _gVAO;
            const IVertexLayout& _vertexLayout;
    };
}