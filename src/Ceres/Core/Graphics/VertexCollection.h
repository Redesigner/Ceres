#pragma once

#include "../Common/Matrix.h"

namespace Ceres
{
    class IndexBuffer;
    class VertexArrayObject;
    class VertexBufferObject;

    struct Vector3;

    class VertexCollection
    {
        public:
            VertexCollection(Vector3 vertices[], unsigned int count, unsigned int indices[], unsigned int icount);
            ~VertexCollection();

            void Render();
            void ApplyTransform(Matrix transform);

        private:
            Matrix _model;
            unsigned int _count;
            IndexBuffer* _iBO;
            VertexArrayObject* _vAO;
            VertexBufferObject* _vBO;
    };
}