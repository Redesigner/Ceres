#include "Mesh.h"

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

namespace Ceres
{
    Mesh::Mesh(IVertexType vertexData[], const IVertexLayout& vertexLayout, int vertexCount, unsigned int indices[], int indexCount,  EffectPtr effect)
    {
        _vertexCount = vertexCount;
        _vAO = new VertexArrayObject(vertexLayout);
        _vBO = new VertexBufferObject(vertexCount, vertexLayout);
        _iB = new IndexBuffer(indexCount);
        _vBO->SetData(vertexData, vertexCount);
        _iB->SetData(indices, indexCount);
        _vAO->SetAttributes();
    }

    Mesh::~Mesh()
    {
        // Each wrapper class should handle its own deletion via OpenGL
        delete _vAO;
        delete _iB;
        delete _vBO;
    }

    int Mesh::Size()
    {
        return _vertexCount;
    }

    EffectPtr Mesh::GetEffect()
    {
        return _effect;
    }
}