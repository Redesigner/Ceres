#pragma once

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    class IndexBuffer;
    class VertexBufferObject;
    
    class VertexArrayObject
    {
        public:
            VertexArrayObject();
            ~VertexArrayObject();

            void Bind();
            void BindTo(VertexBufferObject* vBO);
            void BindTo(IndexBuffer* iBO);

        private:
            GLuint _gVAO;
    };
}