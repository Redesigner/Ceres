#include "Mesh.h"

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include <fmt/core.h>

namespace Ceres
{
    Mesh::Mesh(IVertexType vertexData[], const IVertexLayout& vertexLayout, int vertexCount, unsigned int indices[], int indexCount,  EffectPtr effect)
    {
        _vertexCount = vertexCount;
        _indexCount = indexCount;
        _vAO = new VertexArrayObject(vertexLayout);
        _vBO = new VertexBufferObject(vertexCount, vertexLayout);
        _iB = new IndexBuffer(indexCount);
        _vBO->SetData(vertexData, vertexCount);
        _vAO->SetAttributes();
        _iB->SetData(indices, indexCount);
    }

    Mesh::~Mesh()
    {
        // Each wrapper class should handle its own deletion via OpenGL
        fmt::print("Destroying mesh...");
        delete _vAO;
        delete _iB;
        delete _vBO;
    }

    int Mesh::Size()
    {
        return _indexCount;
    }

    EffectPtr Mesh::GetEffect()
    {
        return _effect;
    }

    VertexArrayObject* Mesh::VertexArray()
    {
        _vAO->Bind();
        return _vAO;
    }
}