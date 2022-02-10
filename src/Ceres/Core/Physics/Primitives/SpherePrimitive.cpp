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
        return VertexList{position};
    }

    float SpherePrimitive::SemiMajorAxis()
    {
        return _radius;
    }

    float SpherePrimitive::GetSphereRadius() const
    {
        return _radius;
    }
}