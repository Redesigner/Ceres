#pragma once

#include "IService.h"

#include <unordered_map>
#include <typeindex>

namespace Ceres
{
    class ServiceContainer
    {
        public:
            ServiceContainer();
            ~ServiceContainer();

                template <typename T>
                void AddService(T* service)
                {
                    _serviceMap.emplace(std::type_index(typeid(T)), service);
                }

                template <typename T>
                T* GetService()
                {
                    return (T*) _serviceMap.at(std::type_index(typeid(T)));
                }
        private:
            std::unordered_map<std::type_index, IService*> _serviceMap;
    };
}