#pragma once


extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}namespace Ceres
{
    class CubeMap
    {
        public:
            CubeMap(const char* textureName);
            CubeMap(const CubeMap&) = delete;
            ~CubeMap();

            GLuint GetID() const;

            void Bind();

        private:
            SDL_Surface* genSurface(const char* textureName);
            void flipSurface(SDL_Surface* surface);
            void rotateSurfaceCW(SDL_Surface* surface);
            void rotateSurfaceCCW(SDL_Surface* surface);
            void rotateSurface180(SDL_Surface* surface);

            GLuint _textureID;
    };
}