#include "IService.h"

#include <stdexcept>

namespace Ceres
{
    IService::IService()
        :_components(ComponentList(4))
    {}

    IService::~IService()
    {}

    ComponentRef IService::GetComponent(unsigned int id)
    {
        return ComponentRef(&_components, id);
    }
}