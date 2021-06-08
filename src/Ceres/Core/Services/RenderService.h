#pragma once

#include "../Graphics/GraphicsDevice.h"
#include "../Components/ComponentList.h"
#include "../Components/ComponentRef.h"
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

            ComponentRef GenerateComponent(std::string typeName, int argCount, void* args) override;
            ComponentRef GetComponent(unsigned int id) override;

            void RenderComponents();
            
        private:
            const GraphicsDevice& _parentDevice;

            ComponentList _components;
    };
}