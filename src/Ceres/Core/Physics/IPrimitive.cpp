#include "IPrimitive.h"

namespace Ceres
{
    IPrimitive::IPrimitive()
    {}

    IPrimitive::~IPrimitive()
    {}

    float IPrimitive::GetSphereRadius() const
    {
        return 0.0f;
    }

    Transform IPrimitive::GetTransform() const
    {
        return _transform;
    }

    void IPrimitive::SetTransform(Transform transform)
    {
        _transform = transform;
    }
}