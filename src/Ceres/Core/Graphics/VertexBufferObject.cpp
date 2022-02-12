#include "VertexBufferObject.h"

#include <vector>

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
        fmt::print("Vertex size: {} bytes each.\n", vertexLayout.Size());
    }
    VertexBufferObject::~VertexBufferObject()
    {
        glDeleteBuffers(1, &_gVBO);
    }

    void VertexBufferObject::SetData(const IVertexType data[], const uint size, const uint offset)
    {
        // fmt::print("Loading {} vertices.\n", size);
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