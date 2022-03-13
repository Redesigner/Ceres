#pragma once

#include "Base/IComponent.h"

#include "../Common/AssetPointer.h"
#include "../Common/Transform.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Texture.h"

namespace Ceres
{
    class MeshComponent : public IComponent
    {
        public:
            MeshComponent(AssetPtr<Mesh> mesh);
            MeshComponent(AssetPtr<Mesh> mesh, AssetPtr<Texture> texture);

            ~MeshComponent();

            virtual bool RecieveMessage(Message& message) override;

            AssetPtr<Mesh> Mesh;
            AssetPtr<Texture> Texture;
            Transform Transform;

        private:
    };
}