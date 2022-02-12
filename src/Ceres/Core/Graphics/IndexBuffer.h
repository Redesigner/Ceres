#pragma once

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

using uint = unsigned int;

namespace Ceres
{    
    class IndexBuffer
    {
        public:
            IndexBuffer(int size);
            ~IndexBuffer();

            void SetData(const uint indices[], const uint count, const uint offset);
            void SetData(const uint indices[], const uint count);
            void Bind() const;

        private:
            GLuint _iBO;
            int _currentCount;
            int _capacity;
    };
}