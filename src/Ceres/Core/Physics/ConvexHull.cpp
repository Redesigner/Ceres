#include "ConvexHull.h"

#include <stdexcept>
#include <fmt/core.h>

namespace Ceres
{
    ConvexHull::ConvexHull(std::vector<Vector3>(vertices))
        :Vertices(vertices)
    {}

    Vector3 ConvexHull::FurthestVertex(Vector3 directionUnit)
    {
        if (Vertices.size() == 0)
        {
            throw std::out_of_range(fmt::format("Convex Hull does not contain any valid vertices"));
        }
        // Assume vector is normalized, do not do it again
        // directionUnit = Transform.GetRotationMatrix().Transpose() * directionUnit;

        float distance = 0;
        Vector3 result = Vertices[0];
        bool initialized = false;
        for (Vector3 vertex : Vertices)
        {
            vertex = Transform.GetMatrix() * vertex;
            float calcDistance = vertex.Dot(directionUnit);
            fmt::print("Vertex at world {}, with distance {}\n", vertex.ToString(), calcDistance);
            if (!initialized || (calcDistance > distance) )
            {
                distance = calcDistance;
                result = vertex;
                initialized = true;
            }
        }
        return result;
    }
}