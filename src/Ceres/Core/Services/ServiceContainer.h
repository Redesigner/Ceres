#pragma once

#include "IService.h"

#include <unordered_map>
#include <string>

namespace Ceres
{
    class ServiceContainer
    {
        public:
            ServiceContainer();
            ~ServiceContainer();

            void AddService(std::string serviceName, IService* service);
            IService* GetService(std::string serviceName);
        private:
            std::unordered_map<std::string, IService*> _serviceMap;
    };
}