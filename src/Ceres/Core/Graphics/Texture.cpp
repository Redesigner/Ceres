#include "Texture.h"

extern "C"
{
    #include "SDL_image.h"
}
#include "fmt/core.h"

const std::string DEBUG_PREFIX = "[texture]";

namespace Ceres
{
    Texture::Texture(const char* textureName)
    {
        SDL_Surface* surface = IMG_Load(textureName);
        if (surface == nullptr)
        {
            fmt::print("{} Failed to load texture: '{}'\n", DEBUG_PREFIX, IMG_GetError());
            return;
        }
        flipSurface(surface);
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        SDL_FreeSurface(surface);
        _textureID = texture;
        fmt::print("{} Loaded texture file successfully: '{}'.\n", DEBUG_PREFIX, textureName);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &_textureID);
    }

    GLuint Texture::GetID() const
    {
        return _textureID;
    }

    void Texture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, _textureID);
    }

    void Texture::flipSurface(SDL_Surface* surface)
    {
        SDL_LockSurface(surface);
        char* swap = new char[surface->pitch];
        char* pixels = static_cast<char*>(surface->pixels);

        for (int i = 0; i < surface->h / 2; i++)
        {
            // get pointers to the two rows to swap
            char* row1 = pixels + i * surface->pitch;
            char* row2 = pixels + (surface->h - i - 1) * surface->pitch;
            
            // swap rows
            memcpy(swap, row1, surface->pitch);
            memcpy(row1, row2, surface->pitch);
            memcpy(row2, swap, surface->pitch);
        }
        delete[] swap;
        SDL_UnlockSurface(surface);
    }
}