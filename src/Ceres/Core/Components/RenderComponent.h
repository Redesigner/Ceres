#pragma once

#include "IComponent.h"

#include "../Common/Transform.h"
#include "../Graphics/Mesh.h"

namespace Ceres
{
    class RenderComponent : IComponent
    {
        public:
            RenderComponent(const IEntity& parent, uint8_t meshId);
            ~RenderComponent();

            uint8_t MeshId;
            Transform Transform;

        private:
    };
}