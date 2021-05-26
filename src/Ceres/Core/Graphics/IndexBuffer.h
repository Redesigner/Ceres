#pragma once

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    class VertexArrayObject;
    
    class IndexBuffer
    {
        public:
            IndexBuffer(unsigned int size);
            ~IndexBuffer();

            void SetData(unsigned int indices[], unsigned int count, unsigned int offset);
            void SetData(unsigned int indices[], unsigned int count);
            void Bind();

        private:
            GLuint _iBO;
            unsigned int _currentCount;
            unsigned int _capacity;
    };
}