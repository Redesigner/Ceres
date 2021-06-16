#include "Effect.h"

#include "Core/IO/ContentManager.h"

#include <fmt/core.h>
#include <stdexcept>

namespace Ceres
{
    Effect::Effect(const char* vertFile, const char* fragFile)
        : _viewProjection(Matrix::Perspective(1280, 720, 90, .1f, 100))
    {
        _glProgram = glCreateProgram();
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);
        _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
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
            SetMatrix("viewProjection", _viewProjection);
            SetVector3("lightPos", Vector3(-15, 15, 40));
        }
    }
    
    Effect::~Effect()
    {
        glDeleteShader(_fragmentShader);
        glDeleteShader(_vertexShader);
        glDeleteProgram(_glProgram);
    }

    void Effect::Begin()
    {
        glUseProgram(_glProgram);
    }

    void Effect::SetMatrix(std::string name, Matrix matrix)
    {
        GLint location = glGetUniformLocation(_glProgram, name.c_str());
        if(location != -1)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, matrix.M[0]);
        }
        else
        {
            fmt::print("Unable to find GL_Uniform {}.\n", name);
        }
    }

    void Effect::SetVector3(std::string name, Vector3 vector)
    {
        GLint location = glGetUniformLocation(_glProgram, name.c_str());
        if(location != -1)
        {
            glUniform3f(location, vector.X, vector.Y, vector.Z);
        }
        else
        {
            fmt::print("Unable to find GL_Uniform {}.\n", name);
        }
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