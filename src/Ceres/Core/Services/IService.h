#pragma once

#include "../Components/Base/ComponentRef.h"

#include <string>

namespace Ceres
{
    class IService
    {
        public:
            IService();
            virtual ~IService();

            virtual ComponentRef GenerateComponent(std::string type, const IEntity& parent, int argCount, void* args) = 0;
            virtual ComponentRef GetComponent(unsigned int id);

        protected:
            ComponentList _components;
    };
}