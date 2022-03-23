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
            /// A renderable instance of a mesh. Renders with an associated texture
            /// if one is specified.
            MeshComponent(AssetPtr<Mesh> mesh, AssetPtr<Texture> texture);
            MeshComponent(AssetPtr<Mesh> mesh);


            ~MeshComponent();

            AssetPtr<Mesh> Mesh;
            AssetPtr<Texture> Texture;
            Transform Transform;

        private:
    };
}