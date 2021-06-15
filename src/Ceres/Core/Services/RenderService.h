#pragma once

#include "../Graphics/GraphicsDevice.h"
#include "../Components/Base/ComponentList.h"
#include "../Components/Base/ComponentRef.h"
#include "IService.h"

namespace Ceres
{
    using EffectPtr = std::shared_ptr<Effect>;
    using MeshPtr = std::shared_ptr<Mesh>;

    class RenderService : public IService
    {
        public:
            RenderService(const GraphicsDevice& graphicsDevice);
            ~RenderService();

            ComponentRef GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args) override;

            void RenderComponents();
            
        private:
            const GraphicsDevice& _parentDevice;
    };
}