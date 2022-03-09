#include "IService.h"

#include <stdexcept>

namespace Ceres
{
    IService::IService()
        :_components(ComponentList())
    {}

    IService::~IService()
    {}

    ComponentRefBase IService::GetComponent(unsigned int id)
    {
        return ComponentRefBase(&_components, id);
    }
}