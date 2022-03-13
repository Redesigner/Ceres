#pragma once

#include "Base/IEntity.h"

#include "../Common/AssetPointer.h"

#include "../Graphics/Mesh.h"
#include "../Graphics/Texture.h"

#include "../Services/ServiceContainer.h"

#include <string>

namespace Ceres
{
    struct IPrimitive;
    
    class Actor : public IEntity
    {
        public:
            Actor(ServiceContainer& serviceContainer);
            ~Actor();

        private:
            std::shared_ptr<IPrimitive> _primitive;
    };
}