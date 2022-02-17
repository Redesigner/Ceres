#pragma once

#include <memory>

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
            Texture(const char* textureName);
            Texture(const Texture&) = delete;
            Texture& operator =(const Texture&) = delete;
            ~Texture();

            GLuint GetID() const;

            void Bind();

        private:
            void flipSurface(SDL_Surface* surface);

            GLuint _textureID;
    };
    using TexturePtr = std::shared_ptr<Texture>;
}