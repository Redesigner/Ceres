#pragma once

#include "Base/IEntity.h"

#include "../Common/AssetPointer.h"

#include "../Graphics/Mesh.h"
#include "../Graphics/Texture.h"

#include "../Services/ServiceContainer.h"

namespace Ceres
{
    struct IPrimitive;
    
    class Actor : public IEntity
    {
        public:
            Actor(ServiceContainer& serviceContainer, AssetPtr<Mesh> mesh, AssetPtr<Texture> texture);
            ~Actor();

        private:
            IPrimitive* _primitive;
    };
}