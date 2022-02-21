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
            VertexArrayObject(VertexArrayObject&& vertexArrayObject);
            ~VertexArrayObject();

            VertexArrayObject& operator=(VertexArrayObject&& vertexArrayObject) noexcept;
            
            void Bind() const;
            void SetAttributes();

        private:
            GLuint _gVAO;
            const IVertexLayout& _vertexLayout;

            bool _initialized = true;
    };
}