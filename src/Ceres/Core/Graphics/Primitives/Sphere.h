#pragma once

#include "../VertexTypes/VertexPositionNormalColor.h"
#include "../VertexTypes/VertexPositionNormalColorLayout.h"
#include "../VertexTypes/IVertexLayout.h"

namespace Ceres
{
    struct Sphere
    {
        public:
            Sphere(float radius, int segments, int rings, Color color);
            ~Sphere();

            VertexPositionNormalColor* Vertices;
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