#pragma once

#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "IndexBuffer.h"

#include "VertexTypes/IVertexLayout.h"

namespace Ceres
{
    class SkyboxVertexLayout : public IVertexLayout
    {
        public:
            virtual void SetAttributes() const override;
            virtual int Size() const override;
            static SkyboxVertexLayout& Get();
    };

    struct SkyboxVertex : public IVertexType
    {
        public:
            SkyboxVertex();
            SkyboxVertex(Vector3 position, Vector3 texCoords);

            Vector3 Position;
            Vector3 TexCoords;
    };

    class Skybox
    {
        public:
            Skybox();
            ~Skybox();

            const VertexArrayObject& GetVertexArray() const;
            const IndexBuffer& GetIndexBuffer() const;

        private:
            void generateSquareFace(int a, int b, int c, int d);

            SkyboxVertex _vertices[8];
            uint _indices[36];

            int _currentIndexCount = 0;

            IndexBuffer _iBO;
            VertexArrayObject _vAO;
            VertexBufferObject _vBO;
    };
}