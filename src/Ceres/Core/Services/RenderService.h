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
            RenderService(GraphicsDevice& graphicsDevice);
            ~RenderService();

            virtual ComponentRef GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args) override;

            void RenderComponents();
            
        private:
            GraphicsDevice& _parentDevice;

            // TODO: How should we handle both types of components when
            // components like cameras can't be rendered?
            ComponentList _renderComponents;
    };
}