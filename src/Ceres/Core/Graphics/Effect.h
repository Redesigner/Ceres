#pragma once
#include <string>

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    class Effect
    {
        public:
            Effect(const char* filepath);
            ~Effect();

            void Attach();
        private:
            void printGlShaderError();
            GLuint _glProgram;
            GLuint _vertexShader;
            std::string _vertexShaderSource;
    };
}