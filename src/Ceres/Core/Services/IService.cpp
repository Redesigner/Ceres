#include "IService.h"

#include <stdexcept>

namespace Ceres
{
    IService::IService()
        :_components(ComponentList())
    {}

    IService::~IService()
    {}

    ComponentPtrBase IService::GetComponent(unsigned int id)
    {
        return ComponentPtrBase(&_components, id);
    }
}