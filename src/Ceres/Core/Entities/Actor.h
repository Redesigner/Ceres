#pragma once

#include "Base/IEntity.h"

#include "../Services/ServiceContainer.h"

namespace Ceres
{
    class Actor : public IEntity
    {
        public:
            Actor(ServiceContainer& serviceContainer);
            ~Actor();
    };
}