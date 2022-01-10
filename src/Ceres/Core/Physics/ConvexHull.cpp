#include "ConvexHull.h"

#include <stdexcept>
#include <cmath>
#include <fmt/core.h>

namespace Ceres
{
    ConvexHull::ConvexHull(std::vector<Vector3>(vertices))
        :_vertices(vertices)
    {}

    std::vector<Vector3> ConvexHull::FurthestVertex(Vector3 directionUnit)
    {
        Vector3 farthestPoint = _vertices[0];
        farthestPoint = GetTransform().GetMatrix() * farthestPoint;
        std::vector<Vector3> points = std::vector<Vector3>();
        points.emplace_back(_vertices[0]);
        float max = farthestPoint.Dot(directionUnit);

        for (int i = 1; i < _vertices.size(); i++)
        {
            Vector3 vertex = GetTransform().GetMatrix() * _vertices[i];
            float distance = vertex.Dot(directionUnit);
            if (distance > max)
            {
                max = distance;
                farthestPoint = vertex;
                points.clear();
                points.emplace_back(vertex);
            }
            else if (distance >= max - Vector3::Epsilon())
            {
                points.emplace_back(vertex);
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