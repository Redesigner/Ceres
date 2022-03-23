#pragma once

#include "VertexTypes/IVertexLayout.h"

#pragma warning(push, 0)
extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}
#pragma warning(pop)

namespace Ceres
{
    /**
     * @brief An OpenGL Vertex Array that defines the internal data layout of any vertex data passed into the buffer
     * 
     */
    class VertexArrayObject
    {
        public:
            VertexArrayObject(const IVertexLayout& vertexLayout);
            VertexArrayObject(VertexArrayObject&& vertexArrayObject) noexcept;
            ~VertexArrayObject();

            VertexArrayObject& operator=(VertexArrayObject&& vertexArrayObject) noexcept;
            
            /**
             * @brief Bind the VAO to the current OpenGL state
             * 
             */
            void Bind() const;
            /**
             * @brief Load the VAO's layout to the current OpenGL state
             * 
             */
            void SetAttributes();

        private:
            GLuint _gVAO;
            const IVertexLayout& _vertexLayout;

            bool _initialized = true;
    };
}