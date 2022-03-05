#include "ServiceContainer.h"

namespace Ceres
{
    ServiceContainer::ServiceContainer()
        :_serviceMap(std::unordered_map<std::type_index, IService*>())
    {}

    ServiceContainer::~ServiceContainer()
    {
        for(auto service : _serviceMap)
        {
            delete service.second;
        }
    }
}