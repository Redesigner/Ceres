#include "Texture.h"

extern "C"
{
    #include "SDL_image.h"
}
#include "fmt/core.h"

const std::string DEBUG_PREFIX = "[texture]";

namespace Ceres
{
    Texture::Texture(std::string textureName)
    {
        SDL_Surface* surface = IMG_Load(textureName.c_str());
        if (surface == nullptr)
        {
            fmt::print("{} Failed to load texture: '{}'\n", DEBUG_PREFIX, IMG_GetError());
            return;
        }
        flipSurface(surface);
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        const int bytesPerPixel = surface->format->BytesPerPixel;
        if (bytesPerPixel == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        SDL_FreeSurface(surface);
        _textureID = texture;
        size_t nameBegin = textureName.rfind('\\') + 1;
        std::string filename = textureName.substr(nameBegin, textureName.length() - nameBegin);
        fmt::print("{} Loaded texture file successfully: '{}'.\n", DEBUG_PREFIX, filename);
    }

    Texture::Texture(Texture&& texture)
    {
        _textureID = texture._textureID;
        texture._initialized = false;
    }

    Texture::~Texture()
    {
        if(_initialized)
        {
            glDeleteTextures(1, &_textureID);
        }
    }

    Texture& Texture::operator=(Texture&& texture)
    {
        this->_textureID = texture._textureID;
        return *this;
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