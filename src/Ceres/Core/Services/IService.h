#pragma once

#include "../Components/ComponentRef.h"

#include <string>

namespace Ceres
{
    class IService
    {
        public:
            IService();
            virtual ~IService();

            virtual ComponentRef GenerateComponent(std::string type, int argCount, void* args) = 0;
            virtual ComponentRef GetComponent(unsigned int id) = 0;
        private:
    };
}