#include "Mesh.h"

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include <fmt/core.h>

namespace Ceres
{
    Mesh::Mesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount, AssetPtr<Effect> effect)
        :_vertexCount(vertexCount), _indexCount(indexCount),
        _vAO(vertexLayout), _vBO(_vertexCount, vertexLayout), _iBO(indexCount), _effect(effect)
    {
        _vBO.SetData(vertexData, vertexCount);
        _vAO.SetAttributes();
        _iBO.SetData(indices, indexCount);
    }
    Mesh::Mesh(Mesh&& mesh)
        :_vertexCount(mesh._vertexCount), _indexCount(mesh._indexCount),
        _vAO(std::move(mesh._vAO)), _vBO(std::move(mesh._vBO)), _iBO(std::move(mesh._iBO)), _effect(mesh._effect)
    {
    }

    Mesh::~Mesh()
    {
    }

    int Mesh::Size() const
    {
        return _indexCount;
    }

    AssetPtr<Effect> Mesh::GetEffect() const
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