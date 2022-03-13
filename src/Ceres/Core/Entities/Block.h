#pragma once

#include "Base/IEntity.h"

#include "../Common/AssetPointer.h"

#include "../Graphics/Mesh.h"
#include "../Graphics/Texture.h"

#include "../Services/ServiceContainer.h"

#include <memory>

namespace Ceres
{
    struct IPrimitive;
    
    class Block : public IEntity
    {
        public:
            Block(ServiceContainer& serviceContainer, float x, float y, float z, std::string mesh);
            Block(ServiceContainer& serviceContainer, float x, float y, float z, std::string mesh, std::string texture);
            ~Block();
        private:
            std::shared_ptr<IPrimitive> _primitive;
    };
}