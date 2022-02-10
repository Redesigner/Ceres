#pragma once

#include "../VertexTypes/VertexPositionNormal.h"
#include "../VertexTypes/VertexPositionNormalLayout.h"
#include "../VertexTypes/IVertexLayout.h"

namespace Ceres
{
    struct Sphere
    {
        public:
            Sphere(float radius, int segments, int rings);
            ~Sphere();

            VertexPositionNormal* Vertices;
            int VertexCount;
            int* Indices;
            int IndexCount;

        private:
            void generateTriangleFace(int a, int b, int c);
            void generateSquareFace(int a, int b, int c, int d);
            void generateRingBottom(int segments);
            void generateRing(int segments, int ringNum);
            void generateRingTop(int segments, int ringCount);

            int _currentIndexCount = 0;
    };
}