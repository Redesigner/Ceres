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

    void ServiceContainer::addTypeAssociation(Type componentType, Type serviceType)
    {
        // Only add association if none exists
        if (_componentTypeMap.find(componentType) == _componentTypeMap.end())
        {
            _componentTypeMap.emplace(componentType, serviceType);
        }
    }
}