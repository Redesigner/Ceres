#include "SpherePrimitive.h"

namespace Ceres
{
    SpherePrimitive::SpherePrimitive(float radius)
        :_radius(radius)
    {}
    
    SpherePrimitive::~SpherePrimitive()
    {}

    VertexList SpherePrimitive::FurthestVertex(Vector3 directionUnit)
    {
        Vector3 position = GetTransform().GetPosition();
        VertexList result = VertexList{position + directionUnit * _radius};
        return result;
    }

    float SpherePrimitive::SemiMajorAxis()
    {
        return _radius;
    }
}