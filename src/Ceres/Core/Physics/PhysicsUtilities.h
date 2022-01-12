#pragma once

#include "../Common/Vector3.h"
#include "../Physics/IPrimitive.h"

#include <vector>
#include <stack>

using VertexStack = std::stack<Ceres::Vector3>;

namespace Ceres
{
    class PhysicsUtilities
    {
    public:
        static bool NearlyZero(Vector3 vector);
        static bool NearlyZero(float a);
        static bool PointBetween(Vector3 a, Vector3 b, Vector3 point);
        static Vector3 GetNormal(Vector3 a, Vector3 b, Vector3 c);
        static bool Colinear(Vector3 a, Vector3 b, Vector3 c);
        static VertexList SupportPoints(IPrimitive& shapeA, IPrimitive& shapeB, Vector3 direction);
        static VertexList GiftWrap(VertexList vertices);

    private:
        static VertexList giftAxis(VertexList& points);

        static void sortByDirection(VertexList& array, Vector3 direction);
        static void quickSort(VertexList& array, std::vector<float>& evals, int l, int r);
        static int hoareParition(VertexList& array, std::vector<float>& evals, int l, int r);
        static void qSwap(VertexList& array, std::vector<float>& evals, int a, int b);

        /// Creates a VertexList from a stack, used only for the GiftWrap function
        static VertexList copyLS(VertexStack& stack);
    };
}