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
            Effect(const char* vertFile, const char* fragFile);
            ~Effect();

            void Begin();

        private:
            bool compileShader(GLuint shader, const char* filename, std::string source);
            void printGlShaderError(GLuint shader);

            GLuint _glProgram;
            GLuint _vertexShader;
            GLuint _fragmentShader;

            std::string _vertexShaderSource;
            std::string _fragmentShaderSource;
    };
}