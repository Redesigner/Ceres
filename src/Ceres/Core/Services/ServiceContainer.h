#pragma once

#include "IService.h"

#include <stdexcept>
#include <unordered_map>
#include <typeindex>

namespace Ceres
{
    using Type = std::type_index;
    
    class ServiceContainer
    {
        public:
            ServiceContainer();
            ~ServiceContainer();

                template <typename T>
                void AddService(T* service)
                {
                    _serviceMap.emplace(Type(typeid(T)), service);
                }

                template <typename T>
                T* GetService()
                {
                    return dynamic_cast<T*>(_serviceMap.at(Type(typeid(T))));
                }

                template <typename ComponentType, typename ServiceType>
                void AddTypeAssociation()
                {
                    if (_componentTypeMap.find(Type(typeid(ComponentType))) == _componentTypeMap.end())
                    {
                        _componentTypeMap.emplace(Type(typeid(ComponentType)), Type(typeid(ServiceType)));
                    }
                }

                template <typename T>
                ComponentRef CreateComponent(std::unique_ptr<ComponentParams> &params)
                {
                    Type componentType = Type(typeid(T));
                    Type serviceType = _componentTypeMap.at(componentType);
                    if (_serviceMap.find(serviceType) == _serviceMap.end())
                    {
                        throw std::invalid_argument(fmt::format("Component type {} is associated with service type {}, but no associated service could be found.", componentType.name(), serviceType.name()));
                    }
                    IService* constructorService = _serviceMap.at(serviceType);
                    return constructorService->GenerateComponent(Type(typeid(T)), params);
                }

        private:
            std::unordered_map<Type, IService*> _serviceMap;
            std::unordered_map<Type, Type> _componentTypeMap;
    };
}