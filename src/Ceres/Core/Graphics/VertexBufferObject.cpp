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

    void VertexBufferObject::SetData(std::vector<float> data, unsigned int offset)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _gVBO);
        glBufferSubData(GL_ARRAY_BUFFER, offset, data.size() * sizeof(GLfloat), data.data());
    }

    void VertexBufferObject::SetData(std::vector<float> data)
    {
        if(_currentIndex >= _capacity)
        {
            throw std::out_of_range("Vertex Buffer Object is already full, cannot set data.");
        }
    }
}