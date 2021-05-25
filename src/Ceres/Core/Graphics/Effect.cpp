#include "Effect.h"

#include "Core/IO/ContentManager.h"

#include <fmt/core.h>
#include <stdexcept>

namespace Ceres
{
    Effect::Effect(const char* filepath)
    {
        _glProgram = glCreateProgram();
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);
        _vertexShaderSource = ContentManager::LoadString(filepath);
        const char* vertexCString = _vertexShaderSource.c_str();
        glShaderSource(_vertexShader, 1, &vertexCString, NULL);

        GLint shaderCompiled = GL_FALSE;
        glCompileShader(_vertexShader);
        glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &shaderCompiled);
        if (shaderCompiled != GL_TRUE)
        {
            printGlShaderError();
        }
    }
    void Effect::Attach()
    {
        glAttachShader(_glProgram, _vertexShader);
    }

    void Effect::printGlShaderError()
    {
        int maxLength = 0;
        int msgLength = 0;
        glGetShaderiv(_vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        char* msg = new char[maxLength];
        glGetShaderInfoLog(_vertexShader, maxLength, &msgLength, msg);
        fmt::print(msg);
    }
}