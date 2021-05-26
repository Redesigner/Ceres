#include "VertexArrayObject.h"

#include "IndexBuffer.h"
#include "VertexBufferObject.h"

namespace Ceres
{
    VertexArrayObject::VertexArrayObject()
    {
        _gVAO = 0;
        glGenVertexArrays(1, &_gVAO);
        glBindVertexArray(_gVAO);
    }

    VertexArrayObject::~VertexArrayObject()
    {
        glDeleteVertexArrays(1, &_gVAO);
    }

    void VertexArrayObject::Bind()
    {
        glBindVertexArray(_gVAO);
    }

    void VertexArrayObject::BindTo(VertexBufferObject* vBO)
    {
        glBindVertexArray(_gVAO);
        vBO->Bind();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0); 
    }

    void VertexArrayObject::BindTo(IndexBuffer* iBO)
    {
        glBindVertexArray(_gVAO);
        iBO->Bind();
    }
}