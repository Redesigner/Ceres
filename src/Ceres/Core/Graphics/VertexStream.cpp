#include "VertexStream.h"

#include <vector>

namespace Ceres
{
    VertexStream::VertexStream(const IVertexLayout& vertexLayout, const int bufferSize, EffectPtr effect)
            :_vertexCount(0), _indexCount(0), _vAO(vertexLayout), _vBO(bufferSize, vertexLayout), _iBO(bufferSize)
    {
    }
    
    VertexStream::~VertexStream()
    {
    }

    void VertexStream::AddData(const IVertexType vertexData[], const uint indices[], const uint vertexCount)
    {
        int offset = _vertexCount;
        
        _vBO.Bind();
        _vBO.SetData(vertexData, vertexCount, offset);
        _vertexCount += vertexCount;

        _vAO.Bind();
        _vAO.SetAttributes();

        _iBO.Bind();
        _iBO.SetData(indices, vertexCount, offset);
        _indexCount += vertexCount;
    }

    void VertexStream::Clear()
    {
        _vertexCount = 0;
        _indexCount = 0;
    }

    int VertexStream::Size()
    {
        return _indexCount;
    }

    EffectPtr VertexStream::GetEffect()
    {
        return _effect;
    }

    const VertexArrayObject& VertexStream::GetVertexArray() const
    {
        return _vAO;
    }

    const IndexBuffer& VertexStream::GetIndexBuffer() const
    {
        return _iBO;
    }
}