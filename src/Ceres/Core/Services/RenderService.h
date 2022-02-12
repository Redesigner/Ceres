#pragma once

#include "../Graphics/GraphicsDevice.h"
#include "IService.h"
#include "../Common/VertexList.h"

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
            
            void LoadWireframeData(const IVertexType vertexData[], const uint indices[], const uint vertexCount);
            void LoadWireframeData(VertexList& vertices);
            void ClearWireframe();
            
        private:
            GraphicsDevice& _parentDevice;
    };
}