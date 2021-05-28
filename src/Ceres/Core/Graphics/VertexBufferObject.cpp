#include "VertexBufferObject.h"

#include <vector>

namespace Ceres
{
    VertexBufferObject::VertexBufferObject(int capacity, const IVertexLayout& vertexLayout)
    {
        _capacity = capacity;
        _currentIndex = 0;
        _gVBO = 0;

        glGenBuffers(1, &_gVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
        glBufferData(GL_ARRAY_BUFFER, _capacity * vertexLayout.Size(), NULL, GL_DYNAMIC_DRAW);
        fmt::print("Vertex size: {} bytes each.\n", vertexLayout.Size());
    }
    VertexBufferObject::~VertexBufferObject()
    {
        glDeleteBuffers(1, &_gVBO);
    }

    void VertexBufferObject::SetData(IVertexType data[], int size, int offset)
    {
        fmt::print("Loading {} vertices.\n", size);
        if(offset + size > _capacity)
        {
            throw std::out_of_range("VertexBufferObject data out of range.");
        }
        _currentIndex += size;
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
        glBufferSubData(GL_ARRAY_BUFFER, offset, 12 * size, data);
    }

    void VertexBufferObject::SetData(IVertexType data[], int size)
    {
        SetData(data, size, _currentIndex);
    }

    void VertexBufferObject::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
    }
}