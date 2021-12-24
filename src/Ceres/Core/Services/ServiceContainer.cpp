#include "ServiceContainer.h"

const int DEFAULT_CONTAINER_SIZE = 5;

namespace Ceres
{
    ServiceContainer::ServiceContainer()
        :_serviceMap(std::unordered_map<std::type_index, IService*>(DEFAULT_CONTAINER_SIZE))
    {}

    ServiceContainer::~ServiceContainer()
    {
        for(auto service : _serviceMap)
        {
            delete service.second;
        }
    }
}