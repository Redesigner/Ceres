#pragma once

#include <memory>
#include <vector>

#include "Mesh.h"
#include "VertexTypes/IVertexType.h"
#include "../Common/Matrix.h"
#include "../Components/RenderComponent.h"

struct SDL_Window;
struct SDL_Surface;

namespace Ceres
{
    class Context;
    class Effect;

    struct Vector3;

    using EffectPtr = std::shared_ptr<Effect>;
    using MeshPtr = std::shared_ptr<Mesh>;

    class GraphicsDevice
    {
        public:

            GraphicsDevice();
            ~GraphicsDevice();

            void BeginRender();
            void EndRender();

            void Render();
            void Render(RenderComponent* renderComponent) const;

            EffectPtr LoadEffect(const char* vertexShaderName, const char* fragmentShaderName);
            uint8_t LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const int vertexCount, const int indices[], const int indexCount);
            
            // TODO: return appropriate type, manage with separate class?


            RenderComponent* CreateRenderComponent(const IEntity& parent, uint8_t meshId) const;

        private:

            void printError();

            void unloadEffects();
            void unloadMeshes();

            SDL_Window* createWindow();
            
            SDL_Window* _window;
            SDL_Surface* _screenSurface;

            Context* _currentContext;
            EffectPtr _currentEffect;

            std::vector<EffectPtr> _loadedEffects;
            std::vector<MeshPtr> _loadedMeshes;

            // std::vector<RenderComponent> _renderComponents;
    };
}