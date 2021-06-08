#include "ServiceContainer.h"

const int DEFAULT_CONTAINER_SIZE = 5;

namespace Ceres
{
    ServiceContainer::ServiceContainer()
        :_serviceMap(std::unordered_map<std::string, IService*>(DEFAULT_CONTAINER_SIZE))
    {

    }

    ServiceContainer::~ServiceContainer()
    {
        for(auto service : _serviceMap)
        {
            delete service.second;
        }
    }

    void ServiceContainer::AddService(std::string serviceName, IService* service)
    {
        _serviceMap.emplace(serviceName, service);
    }

    IService* ServiceContainer::GetService(std::string serviceName)
    {
        return _serviceMap.at(serviceName);
    }
}