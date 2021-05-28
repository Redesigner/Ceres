#pragma once

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{    
    class IndexBuffer
    {
        public:
            IndexBuffer(int size);
            ~IndexBuffer();

            void SetData(unsigned int indices[], int count, int offset);
            void SetData(unsigned int indices[], int count);
            void Bind();

        private:
            GLuint _iBO;
            int _currentCount;
            int _capacity;
    };
}