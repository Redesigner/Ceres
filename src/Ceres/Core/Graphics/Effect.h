#pragma once

#include "../Common/Matrix.h"
#include "../Common/Matrix2D.h"
#include "../Common/Vector3.h"
#include "../Common/AssetPointer.h"

#include "CubeMap.h"
#include "Texture.h"

#include <string>
#include <unordered_map>

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    class CameraComponent;
    class Shadowmap;
    class Effect
    {
        public:
            Effect(const std::string& vertData, const std::string& fragData, const char* shaderName);
            Effect(Effect&) = delete;
            Effect(Effect&& effect);
            ~Effect();

            Effect& operator=(Effect&) = delete;
            Effect& operator=(Effect&& effect);

            void Begin();
            void SetCamera(CameraComponent* camera);
            void SetMatrix(std::string name, Matrix matrix);
            void SetMatrix2D(std::string name, Matrix2D matrix);
            void SetVector3(std::string name, Vector3 vector);
            void SetTexture(std::string name, AssetPtr<Texture> texture);
            void SetTexture(std::string name, Cubemap* cubemap);
            void SetCubemap(std::string name, Cubemap* cubemap);
            void SetShadowmap(Shadowmap* shadowmap);
            void SetViewMatrix(const Matrix& matrix);

            const std::string& GetName() const;

        private:
            bool compileShader(GLuint shader, const std::string& source);
            void printGlShaderError(GLuint shader);
            GLint getUniformLocation(std::string& name);

            GLuint _glProgram;
            GLuint _vertexShader;
            GLuint _fragmentShader;

            std::string _vertexShaderSource;
            std::string _fragmentShaderSource;

            /// A human readable name for this shader
            std::string _name;

            Matrix _viewPosition;

            std::unordered_map<std::string, GLint> _uniformLocationMap;

            bool _initialized = true;
    };
}