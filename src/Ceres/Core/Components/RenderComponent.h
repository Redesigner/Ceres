#pragma once

#include "Base/IComponent.h"

#include "../Common/Transform.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Texture.h"

namespace Ceres
{
    class RenderComponent : public IComponent
    {
        public:
            RenderComponent(const IEntity& parent, uint8_t meshId);
            RenderComponent(const IEntity& parent, uint8_t meshId, uint8_t textureId);

            ~RenderComponent();

            virtual bool RecieveMessage(Message* message) override;

            uint8_t MeshId;
            int TextureId;
            Transform Transform;

        private:
    };
}