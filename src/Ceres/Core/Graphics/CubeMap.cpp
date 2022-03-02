#include "Cubemap.h"

extern "C"
{
    #include "SDL_image.h"
}
#include "fmt/core.h"

#include <vector>

const std::vector<std::string> CUBE_FACE_NAME = {
    "left.png",
    "right.png",
    "back.png",
    "front.png",
    "top.png",
    "bottom.png"
};
const std::string DEBUG_PREFIX = "[texture]";

namespace Ceres
{
    Cubemap::Cubemap(const char* textureName)
    {
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        for (int i = 0; i < 6; i++)
        {
            SDL_Surface* surface = genSurface(fmt::format("{}{}", textureName, CUBE_FACE_NAME[i]).c_str());
            if (i == 1)
            {
                rotateSurfaceCW(surface);
            }
            if (i == 0)
            {
                rotateSurfaceCCW(surface);
            }
            if(i == 2 || i == 5)
            {
                rotateSurface180(surface);
            }
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
            SDL_FreeSurface(surface);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        _textureID = texture;
        fmt::print("{} Loaded cubemap file successfully: '{}'.\n", DEBUG_PREFIX, textureName);
    }

    Cubemap::~Cubemap()
    {
        glDeleteTextures(1, &_textureID);
    }

    GLuint Cubemap::GetID() const
    {
        return _textureID;
    }

    void Cubemap::Bind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
    }

    SDL_Surface* Cubemap::genSurface(const char* textureName)
    {
        SDL_Surface* surface = IMG_Load(textureName);
        if (surface == nullptr)
        {
            fmt::print("{} Failed to load texture: '{}'\n", DEBUG_PREFIX, IMG_GetError());
            return nullptr;
        }
        return surface;
    }

    void Cubemap::flipSurface(SDL_Surface* surface)
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

    void Cubemap::rotateSurfaceCW(SDL_Surface* surface)
    {
        SDL_LockSurface(surface);
        int pixelSize = surface->format->BytesPerPixel;
        char* swap = new char[pixelSize];
        char* pixels = static_cast<char*>(surface->pixels);
        
        int pixelCount = surface->h * surface->w;
        for (int x = 0; x < surface->w / 2; x++)
        {
            for (int y = 0; y < surface->h / 2; y++)
            {
                int i = x + surface->w * y;

                int x2 = surface->w - 1 - y;
                int y2 = x;
                int i2 = x2 + surface->w * y2;

                int x3 = surface->w - 1 - x;
                int y3 = surface->h - 1 - y;
                int i3 = x3 + surface->w * y3;

                int x4 = y;
                int y4 = surface->h - 1 -x;
                int i4 = x4 + surface->w * y4;

                memcpy(swap, pixels + i4 * pixelSize, pixelSize);
                memcpy(pixels + i4 * pixelSize, pixels + i3 * pixelSize, pixelSize);
                memcpy(pixels + i3 * pixelSize, pixels + i2 * pixelSize, pixelSize);
                memcpy(pixels + i2 * pixelSize, pixels + i * pixelSize, pixelSize);
                memcpy(pixels + i * pixelSize, swap, pixelSize);
            }
        }
        delete[] swap;
        SDL_UnlockSurface(surface);
    }

    void Cubemap::rotateSurfaceCCW(SDL_Surface* surface)
    {
        SDL_LockSurface(surface);
        int pixelSize = surface->format->BytesPerPixel;
        char* swap = new char[pixelSize];
        char* pixels = static_cast<char*>(surface->pixels);
        
        int pixelCount = surface->h * surface->w;
        for (int x = 0; x < surface->w / 2; x++)
        {
            for (int y = 0; y < surface->h / 2; y++)
            {
                int i = x + surface->w * y;

                int x2 = surface->w - 1 - y;
                int y2 = x;
                int i2 = x2 + surface->w * y2;

                int x3 = surface->w - 1 - x;
                int y3 = surface->h - 1 - y;
                int i3 = x3 + surface->w * y3;

                int x4 = y;
                int y4 = surface->h - 1 -x;
                int i4 = x4 + surface->w * y4;

                memcpy(swap, pixels + i * pixelSize, pixelSize);
                memcpy(pixels + i * pixelSize, pixels + i2 * pixelSize, pixelSize);
                memcpy(pixels + i2 * pixelSize, pixels + i3 * pixelSize, pixelSize);
                memcpy(pixels + i3 * pixelSize, pixels + i4 * pixelSize, pixelSize);
                memcpy(pixels + i4 * pixelSize, swap, pixelSize);
            }
        }
        delete[] swap;
        SDL_UnlockSurface(surface);
    }

    void Cubemap::rotateSurface180(SDL_Surface* surface)
    {
        SDL_LockSurface(surface);
        int pixelSize = surface->format->BytesPerPixel;
        char* swap = new char[pixelSize];
        char* pixels = static_cast<char*>(surface->pixels);
        
        int pixelCount = surface->h * surface->w;
        for (int x = 0; x < surface->w; x++)
        {
            for (int y = 0; y < surface->h / 2; y++)
            {
                int i = x + surface->w * y;

                int x2 = surface->w - 1 - x;
                int y2 = surface->h - 1 - y;
                int i2 = x2 + surface->w * y2;

                memcpy(swap, pixels + i2 * pixelSize, pixelSize);
                memcpy(pixels + i2 * pixelSize, pixels + i * pixelSize, pixelSize);
                memcpy(pixels + i * pixelSize, swap, pixelSize);
            }
        }
        delete[] swap;
        SDL_UnlockSurface(surface);
    }
}