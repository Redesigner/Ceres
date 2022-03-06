#pragma once

#include "../VertexTypes/IVertexLayout.h"
#include "../VertexTypes/IVertexType.h"

#include <vector>

using uint = unsigned int;

namespace Ceres
{
    struct MeshPrimitiveBase
    {
        public:
            MeshPrimitiveBase(uint vertexCount, uint indexCount);
            virtual ~MeshPrimitiveBase();

            IVertexType* GetVertices() const;
            uint GetVertexCount() const;

            uint* GetIndices() const;
            uint GetIndexCount() const;

            virtual IVertexLayout* GetVertexLayout() const = 0;

        protected:
            const uint _vertexCount;
            
            IVertexType* _vertices;
            uint* _indices;
            const uint _indexCount;
    };
    
    template <typename VertexType>
    struct MeshPrimitive : public MeshPrimitiveBase
    {
        public:
            MeshPrimitive(uint vertexCount, uint indexCount)
                : MeshPrimitiveBase(vertexCount, indexCount)
            {
                _typedVertices = new VertexType[_vertexCount];
                _vertices = static_cast<IVertexType*>(_typedVertices);
            }

            MeshPrimitive(std::vector<VertexType>& vertices, std::vector<int>& indices)
                : MeshPrimitiveBase(vertices.size(), indices.size())
            {
                _typedVertices = new VertexType[_vertexCount];
                _vertices = static_cast<IVertexType*>(_typedVertices);
                memcpy(_typedVertices, vertices.data(), _vertexCount * sizeof(VertexType));
                _indices = new uint[_indexCount];
                memcpy(_indices, indices.data(), _indexCount * sizeof(uint));
            }

            virtual ~MeshPrimitive() override
            {
                delete[] _typedVertices;
            }

            virtual IVertexLayout* GetVertexLayout() const override { return &VertexType::Layout::Get(); }

        protected:
            VertexType* _typedVertices;
    };
}