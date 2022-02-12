#pragma once

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include "VertexTypes/IVertexType.h"

#include <memory>

using uint = unsigned int;
namespace Ceres
{
    class Effect;
    class IVertexLayout;

    using EffectPtr = std::shared_ptr<Effect>;

    class Mesh
    {
        public:
            Mesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount, EffectPtr effect);
            ~Mesh();

            int Size();
            EffectPtr GetEffect();
            const VertexArrayObject& GetVertexArray() const;
            const IndexBuffer& GetIndexBuffer() const;

        private:
            EffectPtr _effect;
            int _vertexCount;
            int _indexCount;
            IndexBuffer _iBO;
            VertexArrayObject _vAO;
            VertexBufferObject _vBO;
    };
}