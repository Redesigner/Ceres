#include "VertexBufferObject.h"

#include <vector>

const std::string DEBUG_PREFIX = "[vertexbuffer]";
namespace Ceres
{
    VertexBufferObject::VertexBufferObject(uint capacity, const IVertexLayout& vertexLayout)
        :_capacity(capacity)
    {
        _currentIndex = 0;
        _gVBO = 0;
        _size = vertexLayout.Size();

        glGenBuffers(1, &_gVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
        glBufferData(GL_ARRAY_BUFFER, _capacity * vertexLayout.Size(), NULL, GL_DYNAMIC_DRAW);
        fmt::print("{} Vertex size: {} bytes each.\n", DEBUG_PREFIX, vertexLayout.Size());
    }
    VertexBufferObject::VertexBufferObject(VertexBufferObject&& vertexBufferObject)
        :_capacity(vertexBufferObject._capacity)
    {
        _currentIndex = vertexBufferObject._currentIndex;
        _gVBO = vertexBufferObject._gVBO;
        _size = vertexBufferObject._size;

        vertexBufferObject._initialized = false;
    }
    VertexBufferObject::~VertexBufferObject()
    {
        if(_initialized)
        {
            glDeleteBuffers(1, &_gVBO);
        }
    }

    void VertexBufferObject::SetData(const IVertexType data[], const uint size, const uint offset)
    {
        fmt::print("{} Loading {} vertices.\n", DEBUG_PREFIX, size);
        if(offset + size > _capacity)
        {
            throw std::out_of_range("VertexBufferObject data out of range.");
        }
        _currentIndex += size;
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
        glBufferSubData(GL_ARRAY_BUFFER, offset, _size * size, data);
    }

    void VertexBufferObject::SetData(const IVertexType data[], const uint size)
    {
        SetData(data, size, _currentIndex);
    }

    void VertexBufferObject::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
    }
}