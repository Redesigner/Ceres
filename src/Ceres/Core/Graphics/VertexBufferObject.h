#pragma once

#include "../Common/Vector3.h"
#include "VertexTypes/IVertexType.h"
#include "VertexTypes/IVertexLayout.h"

#include <vector>
#include <stdexcept>

#pragma warning(push, 0)
extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}
#pragma warning(pop)

using uint = unsigned int;

namespace Ceres
{
    class VertexBufferObject
    {
        public:
            VertexBufferObject(uint capacity, const IVertexLayout& vertexLayout);
            VertexBufferObject(VertexBufferObject&& vertexBufferObject) noexcept;
            ~VertexBufferObject();

            void SetData(const IVertexType data[], const uint size, const uint offset);
            void SetData(const IVertexType data[], const uint size);            

            void Bind();

        private:
            uint _capacity;
            uint _currentIndex;
            uint _size;
            GLuint _gVBO;

            bool _initialized = true;
    };
}