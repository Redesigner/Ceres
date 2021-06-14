#pragma once

#include "Base/IComponent.h"

#include "../Common/Transform.h"
#include "../Graphics/Mesh.h"

namespace Ceres
{
    class RenderComponent : public IComponent
    {
        public:
            RenderComponent(const IEntity& parent, uint8_t meshId);
            ~RenderComponent();

            virtual bool RecieveMessage(Message* message) override;

            uint8_t MeshId;
            Transform Transform;

        private:
    };
}