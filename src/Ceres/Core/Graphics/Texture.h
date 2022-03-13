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
    /**
     * @brief An object containing a GPU-loaded texture
     * 
     */
    class Texture
    {
        public:
            /**
             * @brief Construct a new Texture object
             * 
             * @param filePath Complete path to the texture file to be loaded
             * @param textureName A unique identifier for the texture
             */
            Texture(std::string filePath, std::string textureName);
            Texture(std::string filePath);
            Texture(const Texture&) = delete;
            Texture(Texture&& texture);
            ~Texture();

            Texture& operator =(const Texture&) = delete;
            Texture& operator =(Texture&& texture);

            /**
             * @brief Get the internal OpenGL representation of the texture
             * 
             * @return GLuint
             */
            GLuint GetID() const;
            const std::string& GetName() const;

            /// Bind the texture to the current OpenGL state
            void Bind();

        private:
            void flipSurface(SDL_Surface* surface);

            /// The texture's ID in OpenGL
            GLuint _textureID;
            /// Specified name of the texture, in case we want to get it later
            std::string _name;
            /// Does this object own the associated OpenGL texture?
            /// If so, it's in charge of freeing the texture on the GPU
            /// This value is set to false if the move operator or constructor is called
            bool _initialized = true;
    };
}