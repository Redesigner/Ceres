#pragma once

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include "VertexTypes/IVertexType.h"

#include <memory>

namespace Ceres
{
    class Effect;
    class IVertexLayout;

    using EffectPtr = std::shared_ptr<Effect>;

    class Mesh
    {
        public:
            Mesh(IVertexType vertexData[], const IVertexLayout& vertexLayout, int vertexCount, unsigned int indices[], int indexCount, EffectPtr effect);
            ~Mesh();

            int Size();
            EffectPtr GetEffect();
            const VertexArrayObject& GetVertexArray() const;

        private:
            EffectPtr _effect;
            int _vertexCount;
            int _indexCount;
            IndexBuffer _iBO;
            VertexArrayObject _vAO;
            VertexBufferObject _vBO;
    };
}