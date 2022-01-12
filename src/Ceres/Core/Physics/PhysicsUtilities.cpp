#include "PhysicsUtilities.h"
#include "fmt/core.h"

#define ERROR_THRESHOLD 0.01f

namespace Ceres
{
    bool PhysicsUtilities::NearlyZero(Vector3 vector)
    {
        return (vector.X < ERROR_THRESHOLD && vector.X > -ERROR_THRESHOLD) && (vector.Y < ERROR_THRESHOLD && vector.Y > -ERROR_THRESHOLD) && (vector.Z < ERROR_THRESHOLD && vector.Z > -ERROR_THRESHOLD);
    }

    bool PhysicsUtilities::NearlyZero(float a)
    {
        return (a < ERROR_THRESHOLD && a > -ERROR_THRESHOLD);
    }

    bool PhysicsUtilities::PointBetween(Vector3 a, Vector3 b, Vector3 point)
    {
        Vector3 ab = b - a;
        Vector3 ap = a - point;
        Vector3 bp = b - point;
        return
            (ap.Dot(ab) < 0 && 0 < bp.Dot(ab)) ||
            (ap.Dot(ab) > 0 && 0 > bp.Dot(ab));
    }

    Vector3 PhysicsUtilities::GetNormal(Vector3 a, Vector3 b, Vector3 c)
    {
        return (b - a).Cross(c - a).Normalize();
    }

    bool PhysicsUtilities::Colinear(Vector3 a, Vector3 b, Vector3 c)
    {
        return GetNormal(a, b, c) == Vector3::Zero();
    }

    VertexList PhysicsUtilities::SupportPoints(IPrimitive& shapeA, IPrimitive& shapeB, Vector3 direction)
    {
        VertexList pointsA = shapeA.FurthestVertex(direction);
        VertexList pointsB = shapeB.FurthestVertex(-1 * direction);
        fmt::print("Shape A points: {}\nShape B points: {}\n", pointsA.ToString(), pointsB.ToString());

        VertexList result = VertexList();
        for (Vector3 pointA : pointsA)
        {
            for (Vector3 pointB : pointsB)
            {
                result.Append(pointA - pointB);
            }
        }
        fmt::print("Combined points: {}\n", result.ToString());
        return result;
    }

    VertexList PhysicsUtilities::GiftWrap(VertexList vertices)
    {
        if (vertices.Size() < 3) { return vertices; }
        if (vertices.Size() == 4)
        {
            VertexList lineResult = VertexList(vertices);
            for (int i = 0; i < lineResult.Size(); i++)
            {
                for (int j = i + 1; j < lineResult.Size(); j++)
                {
                    for (int k = lineResult.Size() - 1; k >= 0; k--)
                    {
                        if (k == i || k == j) { continue; }
                        if (PhysicsUtilities::Colinear(vertices[i], vertices[j], vertices[k]) && PhysicsUtilities::PointBetween(vertices[i], vertices[j], vertices[k]))
                        {
                            if (lineResult.Size() == k - 1)
                            {
                                lineResult.RemoveAt(k);
                            }
                        }
                    }
                }
            }
            return lineResult;
        }
        VertexList axes = giftAxis(vertices);

        Vector3 axisY = axes[0];
        Vector3 axisX = axes[1];
        Vector3 normal = axisX.Cross(axisY);

        sortByDirection(vertices, normal);

        Vector3 left = vertices[0];
        Vector3 right = vertices[1];

        VertexStack topRight = VertexStack();
        VertexStack topLeft = VertexStack();

        float leftDot = left.Dot(axisX);
        float rightDot = right.Dot(axisX);
        if (leftDot > rightDot)
        {
            float dot = rightDot;
            rightDot = leftDot;
            leftDot = dot;

            Vector3 point = right;
            right = left;
            left = point;
        }

        topRight.push(right);
        topLeft.push(left);

        float leftSlope = 0;
        float rightSlope = 0;

        bool leftComplete = false;
        bool rightComplete = false;

        for (int i = 2; i < vertices.Size() && (!leftComplete && !rightComplete); i++)
        {
            if (vertices[i] != right && vertices[i] != left)
            {
                float dot = vertices[i].Dot(axisX);
                if (dot == rightDot) { rightComplete = true; }
                else if (dot == leftDot) { leftComplete = true; }
                else if (dot > rightDot && !rightComplete)
                {
                    float dY = (right - vertices[i]).Dot(axisY);
                    if (NearlyZero(dY))
                    {
                        topRight.pop();
                        right = vertices[i];
                        topRight.push(right);
                        rightSlope = 0;
                        rightDot = dot;
                    }
                    else
                    {
                        float slope = dY / (dot - rightDot);
                        if (slope < rightSlope)
                        {
                            right = vertices[i];
                            topRight.push(right);
                            rightSlope = slope;
                            rightDot = dot;
                        }
                    }
                }
                else if (dot < leftDot && !leftComplete)
                {
                    float dy = (left - vertices[i]).Dot(axisY);
                    if (NearlyZero(dy))
                    {
                        topLeft.pop();
                        left = vertices[i];
                        topLeft.push(left);
                        leftSlope = 0;
                        leftDot = dot;
                    }
                    else
                    {
                        float slope = dy / (dot - leftDot);
                        if (slope > leftSlope)
                        {
                            left = vertices[i];
                            topLeft.push(left);
                            leftSlope = slope;
                            leftDot = dot;
                        }
                    }
                }
            }
        }
        left = vertices[vertices.Size() - 2];
        right = vertices[vertices.Size() - 1];
        leftDot = left.Dot(axisX);
        rightDot = right.Dot(axisX);
        if (leftDot > rightDot)
        {
            float dot = rightDot;
            rightDot = leftDot;
            leftDot = dot;

            Vector3 point = right;
            right = left;
            left = point;
        }

        rightComplete = false;
        leftComplete = false;

        VertexStack bottomRight = VertexStack();
        VertexStack bottomLeft = VertexStack();

        if (right == topRight.top()) { rightComplete = true; }
        else { bottomRight.push(right); }
        if (left == topLeft.top()) { leftComplete = true; }
        else { bottomLeft.push(left); }

        leftSlope = 0;
        rightSlope = 0;

        for (int i = vertices.Size() - 3; i > 0 && (!leftComplete && !rightComplete); i--)
        {
            if (vertices[i] != right && vertices[i] != left)
            {
                float dot = vertices[i].Dot(axisX);
                if (dot == rightDot) { rightComplete = true; }
                else if (dot == leftDot) { leftComplete = true; }
                else if (dot > rightDot && !rightComplete)
                {
                    float dy = (right - vertices[i]).Dot(axisY);
                    if (NearlyZero(dy))
                    {
                        bottomRight.pop();
                        right = vertices[i];
                        if (right == topRight.top()) { rightComplete = true; }
                        else { bottomRight.push(right); }

                        rightSlope = 0;
                        rightDot = dot;
                    }
                    else
                    {
                        float slope = dy / (dot - rightDot);
                        if (slope == rightSlope)
                        {
                            topRight.pop();
                        }
                        if (slope > rightSlope)
                        {
                            right = vertices[i];
                            if (right == topRight.top()) { rightComplete = true; }
                            else { bottomRight.push(right); }

                            rightSlope = slope;
                            rightDot = dot;
                        }
                    }
                } 
                else if (dot < leftDot && !leftComplete)
                {
                    float dy = (left - vertices[i]).Dot(axisY);
                    if (NearlyZero(dy))
                    {
                        bottomLeft.pop();
                        left = vertices[i];
                        if (left == topLeft.top()) { leftComplete = true; }
                        else { bottomLeft.push(left); }

                        leftSlope = 0;
                        leftDot = dot;
                    }
                    else
                    {
                        float slope = dy / (dot - leftDot);
                        if (slope < leftSlope)
                        {
                            left = vertices[i];
                            if (left == topLeft.top()) { leftComplete = true; }
                            else { bottomLeft.push(left); }
                            leftSlope = slope;
                            leftDot = dot;
                        }
                    }
                }
            }
        }
        VertexList result = copyLS(topLeft);
        VertexList swap = copyLS(topRight);
        swap.Reverse();
        result.Append(swap);
        result.Append(copyLS(bottomRight));
        swap = copyLS(bottomLeft);
        swap.Reverse();
        result.Append(swap);
        return result;
    }

    VertexList PhysicsUtilities::giftAxis(VertexList& points)
    {
        VertexList result = VertexList(2);
        for (int i = 2; i < points.Size() - 2; i++)
        {
            if (!PhysicsUtilities::Colinear(points[i], points[i + 1], points[i + 2]))
            {
                result[0] = (points[i + 1] - points[i]).Normalize();
                result[1] = result[0].Triple(points[i + 2]).Normalize();
                return result;
            }
        }
        result[0] = Vector3::Up();
        result[1] = Vector3(0.0f, 0.0f, 1.0f);
        return result;
    }

    void PhysicsUtilities::sortByDirection(VertexList& array, Vector3 direction)
    {
        direction = direction.Normalize();
        std::vector<float> evals = std::vector<float>(array.Size());
        for (int i = 0; i < array.Size(); i++)
        {
            evals[i] = array[i].Dot(direction);
        }
        quickSort(array, evals, 0, array.Size() - 1);
    }

    void PhysicsUtilities::quickSort(VertexList& array, std::vector<float>& evals, int l, int r)
    {
        if (l < r)
        {
            int p = hoareParition(array, evals, l, r);
            quickSort(array, evals, l, p);
            quickSort(array, evals, p + 1, r);
        }
    }

    int PhysicsUtilities::hoareParition(VertexList& array, std::vector<float>& evals, int l, int r)
    {
        float p = evals[l];
        int lX = l - 1;
        int rX = r + 1;

        while (true)
        {
            do { lX++; } while (evals[lX] < p);
            do { rX--; } while (evals[rX] > p);
            if (lX >= rX) { return rX; }
            qSwap(array, evals, lX, rX);
        }
    }

    void PhysicsUtilities::qSwap(VertexList& array, std::vector<float>& evals, int a, int b)
    {
        Vector3 aSwap = array[b];
        float eSwap = evals[b];

        array[b] = array[a];
        evals[b] = evals[a];

        array[a] = aSwap;
        evals[a] = eSwap;
    }

    VertexList PhysicsUtilities::copyLS(VertexStack& stack)
    {
        VertexList result = VertexList();
        for (; !stack.empty(); stack.pop())
        {
            result.Append(stack.top());
        }
        return result;
    }
}