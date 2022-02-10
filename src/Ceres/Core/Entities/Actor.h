#pragma once

#include "Base/IEntity.h"

#include "../Services/ServiceContainer.h"

namespace Ceres
{
    struct IPrimitive;
    
    class Actor : public IEntity
    {
        public:
            Actor(ServiceContainer& serviceContainer);
            ~Actor();

        private:
            IPrimitive* _primitive;
    };
}