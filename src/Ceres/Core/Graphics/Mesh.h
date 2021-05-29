#pragma once

#include "VertexTypes/IVertexType.h"

#include <memory>

namespace Ceres
{
    class Effect;
    class IVertexLayout;
    class IndexBuffer;
    class VertexArrayObject;
    class VertexBufferObject;

    using EffectPtr = std::shared_ptr<Effect>;

    class Mesh
    {
        public:
            Mesh(IVertexType vertexData[], const IVertexLayout& vertexLayout, int vertexCount, unsigned int indices[], int indexCount, EffectPtr effect);
            ~Mesh();

            int Size();
            EffectPtr GetEffect();
            VertexArrayObject* VertexArray();

        private:
            EffectPtr _effect;
            int _vertexCount;
            int _indexCount;
            IndexBuffer* _iB;
            VertexArrayObject* _vAO;
            VertexBufferObject* _vBO;
    };
}