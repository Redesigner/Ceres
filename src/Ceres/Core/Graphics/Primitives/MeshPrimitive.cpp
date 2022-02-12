#include "MeshPrimitive.h"

namespace Ceres
{
    MeshPrimitiveBase::MeshPrimitiveBase(uint vertexCount, uint indexCount)
        :_vertexCount(vertexCount), _indexCount(indexCount)
    {}

    MeshPrimitiveBase::~MeshPrimitiveBase()
    {
        delete[] _indices;
    }

    IVertexType* MeshPrimitiveBase::GetVertices() const
    {
        return _vertices;
    }

    uint* MeshPrimitiveBase::GetIndices() const
    {
        return _indices;
    }

    uint MeshPrimitiveBase::GetVertexCount() const
    {
        return _vertexCount;
    }

    uint MeshPrimitiveBase::GetIndexCount() const
    {
        return _indexCount;
    }
}