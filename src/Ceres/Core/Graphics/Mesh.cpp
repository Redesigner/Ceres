#include "Mesh.h"

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include <fmt/core.h>

namespace Ceres
{
    Mesh::Mesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount, AssetPtr<Effect> effect, std::string name)
        :_vertexCount(vertexCount), _indexCount(indexCount),
        _vAO(vertexLayout), _vBO(_vertexCount, vertexLayout), _iBO(indexCount), _effect(effect), _name(name)
    {
        _vBO.SetData(vertexData, vertexCount);
        _vAO.SetAttributes();
        _iBO.SetData(indices, indexCount);
    }
    Mesh::Mesh(Mesh&& mesh) noexcept
        :_vertexCount(mesh._vertexCount), _indexCount(mesh._indexCount),
        _vAO(std::move(mesh._vAO)), _vBO(std::move(mesh._vBO)), _iBO(std::move(mesh._iBO)), _effect(mesh._effect), _name(mesh._name)
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

    const std::string& Mesh::GetName() const
    {
        return _name;
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