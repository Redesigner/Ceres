#include "Mesh.h"

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include <fmt/core.h>

namespace Ceres
{
    Mesh::Mesh(IVertexType vertexData[], const IVertexLayout& vertexLayout, int vertexCount, unsigned int indices[], int indexCount,  EffectPtr effect)
        :_vertexCount(vertexCount), _indexCount(indexCount),
        _vAO(vertexLayout), _vBO(_vertexCount, vertexLayout), _iBO(indexCount)
    {
        _vBO.SetData(vertexData, vertexCount);
        _vAO.SetAttributes();
        _iBO.SetData(indices, indexCount);
    }

    Mesh::~Mesh()
    {
    }

    int Mesh::Size()
    {
        return _indexCount;
    }

    EffectPtr Mesh::GetEffect()
    {
        return _effect;
    }

    const VertexArrayObject& Mesh::GetVertexArray() const
    {
        return _vAO;
    }
}