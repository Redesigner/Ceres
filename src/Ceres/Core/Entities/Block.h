#pragma once

#include "Base/IEntity.h"

#include "../Services/ServiceContainer.h"

namespace Ceres
{
    struct IPrimitive;
    
    class Block : public IEntity
    {
        public:
            Block(ServiceContainer& serviceContainer, float x, float y, float z);
            ~Block();
        private:
            IPrimitive* _primitive;
    };
}