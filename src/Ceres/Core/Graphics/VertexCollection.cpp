#include "VertexCollection.h"

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

namespace Ceres
{
    VertexCollection::VertexCollection(Vector3 vertices[], unsigned int count, unsigned int indices[], unsigned int icount)
    {
        _count = icount;
        _vAO = new VertexArrayObject();
        _vBO = new VertexBufferObject(count);
        _iBO = new IndexBuffer(icount);
        _vBO->SetData(vertices, count);
        _iBO->SetData(indices, icount);
        _vAO->BindTo(_vBO);
        _vAO->BindTo(_iBO);
    }

    VertexCollection::~VertexCollection()
    {
        delete _iBO;
        delete _vBO;
        delete _vAO;
    }

    void VertexCollection::Render()
    {
        _vAO->Bind();
        _vAO->BindTo(_vBO);
        _vAO->BindTo(_iBO);
        glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, NULL);
    }
}