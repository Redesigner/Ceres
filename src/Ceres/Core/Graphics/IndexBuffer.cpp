#include "IndexBuffer.h"

#include <stdexcept>

const GLsizei INDEXSIZE = sizeof(unsigned int);

namespace Ceres
{
    IndexBuffer::IndexBuffer(int size)
        :_capacity(size)
    {
        _iBO = 0;
        _currentCount = 0;
        
        glGenBuffers(1, &_iBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEXSIZE * _capacity, NULL, GL_DYNAMIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &_iBO);
    }

    void IndexBuffer::SetData(const uint indices[], const uint count, const uint offset)
    {
        if(offset + count > _capacity)
        {
            throw std::out_of_range("IndexBuffer data out of range.");
        }
        _currentCount += count;
        Bind();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, count * INDEXSIZE, indices);
    }

    void IndexBuffer::SetData(const uint indices[], const uint count)
    {
        SetData(indices, count, _currentCount);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iBO);
    }
}