#pragma once

#include "MeshPrimitive.h"

#include "../VertexTypes/VertexPositionNormalColor.h"
#include "../VertexTypes/VertexPositionNormalColorLayout.h"

namespace Ceres
{
    struct Sphere : public MeshPrimitive<VertexPositionNormalColor>
    {
        public:
            Sphere(float radius, int segments, int rings, Color color);
            ~Sphere();

        private:
            void generateTriangleFace(int a, int b, int c);
            void generateSquareFace(int a, int b, int c, int d);
            void generateRingBottom(int segments);
            void generateRing(int segments, int ringNum);
            void generateRingTop(int segments, int ringCount);

            int _currentIndexCount = 0;
    };
}