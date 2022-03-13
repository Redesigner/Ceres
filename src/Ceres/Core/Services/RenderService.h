#pragma once

#include "../Graphics/GraphicsDevice.h"
#include "IService.h"
#include "../Common/VertexList.h"
#include "../Common/AssetPointer.h"

#include "../Components/Base/ComponentParameters.h"

namespace Ceres
{
    using EffectPtr = std::shared_ptr<Effect>;
    using MeshPtr = std::shared_ptr<Mesh>;

    class RenderService : public IService
    {
        public:
            RenderService(GraphicsDevice& graphicsDevice);
            ~RenderService();

            virtual ComponentPtrBase GenerateComponent(Type type, ComponentPR& params) override;
            AssetPtr<Texture> GetTexture(std::string textureName);
            AssetPtr<Effect> GetEffect(std::string effectName);
            AssetPtr<Mesh> GetMesh(std::string meshName);
            
        private:
            GraphicsDevice& _parentDevice;
    };
}