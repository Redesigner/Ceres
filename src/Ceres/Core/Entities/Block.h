#pragma once

#include "Base/IEntity.h"

#include "../Common/AssetPointer.h"

#include "../Graphics/Mesh.h"

#include "../Services/ServiceContainer.h"

namespace Ceres
{
    struct IPrimitive;
    
    class Block : public IEntity
    {
        public:
            Block(ServiceContainer& serviceContainer, float x, float y, float z, AssetPtr<Mesh> mesh);
            ~Block();
        private:
            IPrimitive* _primitive;
    };
}