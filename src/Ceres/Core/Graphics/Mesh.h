#pragma once

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include "VertexTypes/IVertexType.h"

#include <memory>

#include "../Common/AssetPointer.h"

using uint = unsigned int;
namespace Ceres
{
    class Effect;
    class IVertexLayout;

    using EffectPtr = std::shared_ptr<Effect>;

    class Mesh
    {
        public:
            Mesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount, AssetPtr<Effect> effect);
            Mesh(Mesh&& mesh);
            Mesh(const Mesh&) = delete;
            ~Mesh();

            Mesh& operator= (const Mesh&) = delete;

            int Size() const;
            AssetPtr<Effect> GetEffect() const;
            const VertexArrayObject& GetVertexArray() const;
            const IndexBuffer& GetIndexBuffer() const;

        private:
            AssetPtr<Effect> _effect;
            int _vertexCount;
            int _indexCount;
            IndexBuffer _iBO;
            VertexArrayObject _vAO;
            VertexBufferObject _vBO;
    };
}