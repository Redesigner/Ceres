#pragma once

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    class VertexBufferObject;
    
    class VertexArrayObject
    {
        public:
            VertexArrayObject();
            ~VertexArrayObject();

            void Bind(VertexBufferObject* vBO);

        private:
            GLuint _gVAO;
    };
}