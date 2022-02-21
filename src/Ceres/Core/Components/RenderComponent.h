#pragma once

#include "Base/IComponent.h"

#include "../Common/AssetPointer.h"
#include "../Common/Transform.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Texture.h"

namespace Ceres
{
    class RenderComponent : public IComponent
    {
        public:
            RenderComponent(const IEntity& parent, AssetPtr<Mesh> mesh);
            RenderComponent(const IEntity& parent, AssetPtr<Mesh> mesh, AssetPtr<Texture> texture);

            ~RenderComponent();

            virtual bool RecieveMessage(Message* message) override;

            AssetPtr<Mesh> Mesh;
            AssetPtr<Texture> Texture;
            Transform Transform;

        private:
    };
}