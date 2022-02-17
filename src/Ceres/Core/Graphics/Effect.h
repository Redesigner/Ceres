#pragma once

#include "../Common/Matrix.h"
#include "../Common/Vector3.h"
#include "../Graphics/Texture.h"

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
            void SetMatrix(std::string name, Matrix matrix);
            void SetVector3(std::string name, Vector3 vector);
            void SetSampler(std::string name, const Texture& texture);
            void SetViewMatrix(const Matrix& matrix);
            void SetFrustrum(const Matrix& matrix);

        private:
            bool compileShader(GLuint shader, const char* filename, std::string source);
            void printGlShaderError(GLuint shader);

            GLuint _glProgram;
            GLuint _vertexShader;
            GLuint _fragmentShader;

            std::string _vertexShaderSource;
            std::string _fragmentShaderSource;

            Matrix _frustrum;
            Matrix _viewPosition;
    };
}