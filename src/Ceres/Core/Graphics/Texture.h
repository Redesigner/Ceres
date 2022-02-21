#pragma once

#include <memory>
#include <string>

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    class Texture
    {
        public:
            Texture(std::string textureName);
            Texture(const Texture&) = delete;
            Texture(Texture&& texture);
            ~Texture();

            Texture& operator =(const Texture&) = delete;
            Texture& operator =(Texture&& texture);

            GLuint GetID() const;

            void Bind();

        private:
            void flipSurface(SDL_Surface* surface);

            GLuint _textureID;
            bool _initialized = true;
    };
}