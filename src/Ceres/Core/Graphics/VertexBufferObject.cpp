#include "VertexBufferObject.h"

#include <vector>
#include <stdexcept>

const GLsizei VERTEXSIZE = 3 * sizeof(GLfloat);

namespace Ceres
{
    VertexBufferObject::VertexBufferObject(unsigned int vertexCount)
    {
        _capacity = vertexCount;
        _currentIndex = 0;
        _gVBO = 0;

        glGenBuffers(1, &_gVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
        glBufferData(GL_ARRAY_BUFFER, VERTEXSIZE * _capacity, NULL, GL_DYNAMIC_DRAW);
    }

    VertexBufferObject::~VertexBufferObject()
    {
        glDeleteBuffers(1, &_gVBO);
    }

    void VertexBufferObject::SetData(std::vector<Vector3> data, unsigned int offset)
    {
        if(offset + data.size() > _capacity)
        {
            throw std::out_of_range("VertexBufferObject data out of range.");
        }
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
        glBufferSubData(GL_ARRAY_BUFFER, offset, data.size() * VERTEXSIZE, data.data());
    }

    void VertexBufferObject::SetData(std::vector<Vector3> data)
    {
        SetData(data, _currentIndex);
    }

    void VertexBufferObject::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
    }
}