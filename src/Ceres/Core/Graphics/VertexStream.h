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
    class IVertexType;

    using EffectPtr = std::shared_ptr<Effect>;

    class VertexStream
    {
        public:
            VertexStream(const IVertexLayout& vertexLayout, const int bufferSize, EffectPtr effect);
            ~VertexStream();

            void AddData(const IVertexType vertexData[], const uint indices[], const uint vertexCount);
            void Clear();

            int Size();
            EffectPtr GetEffect();
            const VertexArrayObject& GetVertexArray() const;
            const IndexBuffer& GetIndexBuffer() const;

        private:
            EffectPtr _effect;
            int _vertexCount;
            int _indexCount;
            // TODO: Reallocate VBO if overflow, eliminate need for IBO
            IndexBuffer _iBO;
            VertexArrayObject _vAO;
            VertexBufferObject _vBO;
    };
}