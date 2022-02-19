#include "Skybox.h"

namespace Ceres
{
    void SkyboxVertexLayout::SetAttributes() const
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Size(), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Size(), reinterpret_cast<void*>(sizeof(Vector3)));
    }

    int SkyboxVertexLayout::Size() const
    {
        return sizeof(Vector3) * 2;
    }

    SkyboxVertexLayout& SkyboxVertexLayout::Get()
    {
        static SkyboxVertexLayout layout;
        return layout;
    }

    SkyboxVertex::SkyboxVertex()
    {}

    SkyboxVertex::SkyboxVertex(Vector3 position, Vector3 texCoords)
        : Position(position), TexCoords(texCoords)
    {}

    Skybox::Skybox()
        :_vAO(SkyboxVertexLayout::Get()), _vBO(8, SkyboxVertexLayout::Get()), _iBO(36)
    {
        float x = 0.5f;
        using Vertex = SkyboxVertex;

        // Bottom
        _vertices[0] = Vertex(Vector3( x,  x, -x),  Vector3( -1, -1, -1));
        _vertices[1] = Vertex(Vector3( x, -x, -x),  Vector3(  1, -1, -1));
        _vertices[2] = Vertex(Vector3(-x, -x, -x),  Vector3(  1, -1,  1));
        _vertices[3] = Vertex(Vector3(-x,  x, -x),  Vector3( -1, -1,  1));
        // Top
        _vertices[4] = Vertex(Vector3( x,  x,  x),  Vector3( -1,  1, -1));
        _vertices[5] = Vertex(Vector3( x, -x,  x),  Vector3(  1,  1, -1));
        _vertices[6] = Vertex(Vector3(-x, -x,  x),  Vector3(  1,  1,  1));
        _vertices[7] = Vertex(Vector3(-x,  x,  x),  Vector3( -1,  1,  1));

        // Top inverted
        generateSquareFace(4, 5, 7, 6);
        // Bottom inverted
        generateSquareFace(3, 2, 0, 1);
        // Front inverted
        generateSquareFace(5, 4, 1, 0);
        // Back inverted
        generateSquareFace(7, 6, 3, 2);
        // Right inverted
        generateSquareFace(6, 5, 2, 1);
        // Left inverted
        generateSquareFace(4, 7, 0, 3);

        _vBO.SetData(_vertices, 8);
        _vAO.SetAttributes();
        _iBO.SetData(_indices, 36);
    }

    Skybox::~Skybox()
    {
    }

    const VertexArrayObject& Skybox::GetVertexArray() const
    {
        return _vAO;
    }

    const IndexBuffer& Skybox::GetIndexBuffer() const
    {
        return _iBO;
    }

    void Skybox::generateSquareFace(int a, int b, int c, int d)
    {
        /*
            a___b
            |  /|
            c/__d
        */
        _indices[_currentIndexCount    ] = a;
        _indices[_currentIndexCount + 1] = b;
        _indices[_currentIndexCount + 2] = c;
        _indices[_currentIndexCount + 3] = b;
        _indices[_currentIndexCount + 4] = d;
        _indices[_currentIndexCount + 5] = c;
        _currentIndexCount += 6;
    }
}