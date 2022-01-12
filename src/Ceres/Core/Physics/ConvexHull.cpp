#include "ConvexHull.h"


#include "PhysicsUtilities.h"

#include <stdexcept>
#include <cmath>
#include <fmt/core.h>

namespace Ceres
{
    ConvexHull::ConvexHull(VertexList(vertices))
        :_vertices(vertices)
    {}

    VertexList ConvexHull::FurthestVertex(Vector3 directionUnit)
    {
        Vector3 farthestPoint = GetTransform().GetMatrix() * _vertices[0];
        VertexList points = VertexList();
        points.Append(farthestPoint);
        float max = farthestPoint.Dot(directionUnit);

        for (int i = 1; i < _vertices.Size(); i++)
        {
            Vector3 vertex = GetTransform().GetMatrix() * _vertices[i];
            float distance = vertex.Dot(directionUnit);
            if (distance > max)
            {
                max = distance;
                farthestPoint = vertex;
                points.Clear();
                points.Append(vertex);
            }
            else if (distance >= max - Vector3::Epsilon())
            {
                points.Append(vertex);
            }
        }
        return points;
    }

    float ConvexHull::SemiMajorAxis()
    {
        if (_semiMajorAxisCached)
        {
            return _semiMajorAxis;
        }

        // TODO: calculate Major Axis and divide by half
        _semiMajorAxis = 0.0f;
        for (Vector3 vertex : _vertices)
        {
            vertex = GetTransform().GetScaleMatrix() * vertex;
            float lengthSquared = vertex.LengthSquared();
            if (vertex.LengthSquared() >= _semiMajorAxis)
            {
                _semiMajorAxis = lengthSquared;
            }
        }
        _semiMajorAxisCached = true;
        _semiMajorAxis = std::sqrt(_semiMajorAxis);
        return _semiMajorAxis;
    }

    void ConvexHull::SetTransform(Transform transform)
    {
        if (!(GetTransform().GetScale() == transform.GetScale()))
        {
            _semiMajorAxisCached = false;
        }
        IPrimitive::SetTransform(transform);
    }

    bool ConvexHull::nearlyEqual(float a, float b)
    {
        float diff = b - a;
        // quick absolute
        diff = diff < 0 ? diff * -1 : diff;
        return diff <= Vector3::Epsilon();
    }
}