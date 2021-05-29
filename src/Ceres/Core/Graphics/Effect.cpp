#include "Effect.h"

#include "Core/IO/ContentManager.h"

#include <fmt/core.h>
#include <stdexcept>

namespace Ceres
{
    Effect::Effect(const char* vertFile, const char* fragFile)
    {
        _glProgram = glCreateProgram();
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);
        _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        _viewProjection = Matrix::Perspective(1.77f, 1, 1, 20);
        Matrix translation = Matrix::Translation(0, -2, -20);
        _viewProjection = translation * _viewProjection;
        if(compileShader(_vertexShader, vertFile, _vertexShaderSource) && compileShader(_fragmentShader, fragFile, _fragmentShaderSource))
        {
            glAttachShader(_glProgram, _vertexShader);
            glAttachShader(_glProgram, _fragmentShader);
            
            glLinkProgram(_glProgram);

            GLint status = GL_TRUE;
            glGetProgramiv(_glProgram, GL_LINK_STATUS, &status);
            if(status != GL_TRUE)
            {
                int maxLength = 0;
                int msgLength = 0;
                glGetProgramiv(_glProgram, GL_INFO_LOG_LENGTH, &maxLength);
                char* msg = new char[maxLength];
                glGetProgramInfoLog(_glProgram, maxLength, &msgLength, msg);
                fmt::print(msg);
                throw std::runtime_error("OpenGL shaders failed to compile.");
            }
            glUseProgram(_glProgram);
            glUniformMatrix4fv(0, 1, GL_FALSE, _viewProjection.M[0]);
        }
    }
    
    Effect::~Effect()
    {
        
    }

    void Effect::Begin()
    {
        glUseProgram(_glProgram);
    }

    bool Effect::compileShader(GLuint shader, const char* filename, std::string source)
    {
        source = ContentManager::LoadString(filename);
        const char* sourceArray = source.c_str();
        glShaderSource(shader, 1, &sourceArray, NULL);

        GLint shaderCompiled = GL_FALSE;
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
        if (shaderCompiled != GL_TRUE)
        {
            printGlShaderError(shader);
            return false;
        }
        return true;
    }

    void Effect::printGlShaderError(GLuint shader)
    {
        int maxLength = 0;
        int msgLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* msg = new char[maxLength];
        glGetShaderInfoLog(shader, maxLength, &msgLength, msg);
        fmt::print(msg);
    }
}