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

            void Render();

            EffectPtr LoadEffect(const char* vertexShaderName, const char* fragmentShaderName);
            uint8_t LoadMesh(IVertexType vertexData[], const IVertexLayout& vertexLayout, int vertexCount, unsigned int indices[], int indexCount);
            
            // TODO: return appropriate type, manage with separate class?
            uint8_t CreateRenderComponent(uint8_t meshId);
            RenderComponent& GetRenderComponent(uint8_t id) { return _renderComponents[id]; }

        private:
            void beginRender();
            void endRender();
            void printError();

            void unloadEffects();
            void unloadMeshes();

            SDL_Window* createWindow();
            
            SDL_Window* _window;
            SDL_Surface* _screenSurface;

            Context* _currentContext;
            EffectPtr _currentEffect;
            Matrix _defaultModelMatrix;

            std::vector<EffectPtr> _loadedEffects;
            std::vector<MeshPtr> _loadedMeshes;

            std::vector<RenderComponent> _renderComponents;
    };
}