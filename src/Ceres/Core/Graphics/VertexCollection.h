#pragma once

#include "../Common/Matrix.h"
#include "VertexTypes/IVertexType.h"
#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include <fmt/core.h>

extern "C"
{
    #include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{

    struct Vector3;

    template <typename V>
    class VertexCollection
    {
        public:
            VertexCollection(V vertices[], unsigned int count, unsigned int indices[], unsigned int icount)
            {
                _model = Matrix::Identity();
                _count = icount;
                _vAO = new VertexArrayObject<V>();
                _vBO = new VertexBufferObject<V>(count);
                _iBO = new IndexBuffer(icount);
                _vBO->SetData(vertices, count);
                vertices->SetAttributes();
                _iBO->SetData(indices, icount);
                _vAO->BindTo(_vBO);
                _vAO->BindTo(_iBO);
            }
            ~VertexCollection()
            {
                delete _iBO;
                delete _vBO;
                delete _vAO;
            }

            void Render()
            {
                _vAO->Bind();
                _vAO->BindTo(_vBO);
                _vAO->BindTo(_iBO);
                glUniformMatrix4fv(1, 1, GL_FALSE, _model.M[0]);
                glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, NULL);
            }

            void ApplyTransform(Matrix transform)
            {
                _model = _model * transform;
            }
            
        private:
            Matrix _model;
            unsigned int _count;
            IndexBuffer* _iBO;
            VertexArrayObject<V>* _vAO;
            VertexBufferObject<V>* _vBO;
    };
}