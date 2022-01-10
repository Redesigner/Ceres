#include "IPrimitive.h"

namespace Ceres
{
    IPrimitive::IPrimitive()
    {}

    IPrimitive::~IPrimitive()
    {}

    Transform IPrimitive::GetTransform()
    {
        return _transform;
    }

    void IPrimitive::SetTransform(Transform transform)
    {
        _transform = transform;
    }
}