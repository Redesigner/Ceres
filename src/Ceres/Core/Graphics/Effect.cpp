#include "Effect.h"

#include "Core/IO/ContentManager.h"
#include "Shadowmap.h"

#include <fmt/core.h>
#include <stdexcept>

namespace Ceres
{
    Effect::Effect(const char* vertFile, const char* fragFile)
        : _frustrum(Matrix::Perspective(1280, 720, 90, .1f, 100.f))
    {
        _glProgram = glCreateProgram();
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);
        _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        _viewPosition = Matrix::Translation(0, -2, -20);
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
                delete[] msg;
                throw std::runtime_error("OpenGL shaders failed to compile.");
            }
            glUseProgram(_glProgram);
            SetMatrix("viewProjection", _viewPosition * _frustrum);
            SetVector3("lightPos", Vector3(0, -1000, 100));
        }
    }

    Effect::Effect(Effect&& effect)
        : _frustrum(effect._frustrum)
    {
        _glProgram = effect._glProgram;
        _vertexShader = effect._vertexShader;
        _fragmentShader = effect._fragmentShader;
        _viewPosition = effect._viewPosition;

        effect._initialized = false;
    }
    
    Effect::~Effect()
    {
        if(_initialized)
        {
            glDeleteShader(_fragmentShader);
            glDeleteShader(_vertexShader);
            glDeleteProgram(_glProgram);
        }
    }

    void Effect::Begin()
    {
        glUseProgram(_glProgram);
    }

    void Effect::SetMatrix(std::string name, Matrix matrix)
    {
        GLint location = getUniformLocation(name);
        if (location == -1)
        {
            fmt::print("[glShader] Unable to find GL_Uniform {}.\n", name);
            return;
        }
        glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
    }

    void Effect::SetVector3(std::string name, Vector3 vector)
    {
        GLint location = getUniformLocation(name);
        if (location == -1)
        {
            fmt::print("[glShader] Unable to find GL_Uniform {}.\n", name);
            return;
        }
        glUniform3f(location, vector.X, vector.Y, vector.Z);
    }

    void Effect::SetTexture(std::string name, AssetPtr<Texture> texture)
    {
        GLint location = getUniformLocation(name);
        if (location == -1)
        {
            fmt::print("[glShader] Unable to find GL_Uniform {}.\n", name);
            return;
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetID());
        glUniform1i(location, 0);
    }

    void Effect::SetTexture(std::string name, Cubemap* cubemap)
    {
        GLint location = getUniformLocation(name);
        if (location == -1)
        {
            fmt::print("[glShader] Unable to find GL_Uniform {}.\n", name);
            return;
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->GetID());
        glUniform1i(location, 0);
    }

    void Effect::SetCubemap(std::string name, Cubemap* cubemap)
    {
        GLint location = getUniformLocation(name);
        if (location == -1)
        {
            fmt::print("[glShader] Unable to find GL_Uniform {}.\n", name);
            return;
        }
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->GetID());
        glUniform1i(location, 1);
    }

    void Effect::SetShadowmap(Shadowmap* shadowmap)
    {
        GLint location = getUniformLocation(std::string("shadowmap"));
        if (location == -1)
        {
            fmt::print("[glShader] Unable to find GL_Uniform shadowmap.\n");
            return;
        }
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, shadowmap->GetID());
        glUniform1i(location, 2);
    }

    void Effect::SetViewMatrix(const Matrix& matrix)
    {
        _viewPosition = matrix;
        SetMatrix("viewProjection", _viewPosition * _frustrum);
    }

    void Effect::SetFrustrum(const Matrix& matrix)
    {
        _frustrum = matrix;
    }


    // Private methods
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
        fmt::print("[glshader] [compile] {}\n", msg);
        delete[] msg;
    }
    
    GLint Effect::getUniformLocation(std::string& name)
    {
        GLint location = 0;
        auto locationIterator = _uniformLocationMap.find(name);
        if (locationIterator != _uniformLocationMap.end())
        {
            location = locationIterator->second;
        }
        else
        {
            location = glGetUniformLocation(_glProgram, name.c_str());
            // store the value for later, even if it's -1
            _uniformLocationMap.insert({name, location});
        }
        return location;
    }
}