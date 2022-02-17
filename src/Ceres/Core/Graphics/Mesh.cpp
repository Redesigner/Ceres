#include "Mesh.h"

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include <fmt/core.h>

namespace Ceres
{
    Mesh::Mesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount,  EffectPtr effect)
        :_vertexCount(vertexCount), _indexCount(indexCount),
        _vAO(vertexLayout), _vBO(_vertexCount, vertexLayout), _iBO(indexCount), _effect(effect)
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

    const IndexBuffer& Mesh::GetIndexBuffer() const
    {
        return _iBO;
    }
}