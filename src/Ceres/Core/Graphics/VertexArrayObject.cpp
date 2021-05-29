#include "VertexArrayObject.h"

#include "VertexTypes/IVertexLayout.h"

namespace Ceres
{
    VertexArrayObject::VertexArrayObject(const IVertexLayout& vertexLayout)
        :_vertexLayout(vertexLayout) 
    {
        _gVAO = 0;
        glGenVertexArrays(1, &_gVAO);
        glBindVertexArray(_gVAO);
    }
    VertexArrayObject::~VertexArrayObject()
    {
        glDeleteVertexArrays(1, &_gVAO);
    }

    void VertexArrayObject::Bind() const
    {
        glBindVertexArray(_gVAO);
    }

    void VertexArrayObject::SetAttributes()
    {
        _vertexLayout.SetAttributes();
    }
}