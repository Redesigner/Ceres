#pragma once

#include <memory>
#include <vector>

#include "Mesh.h"
#include "Primitives/MeshPrimitive.h"
#include "VertexTypes/IVertexType.h"
#include "../Common/Matrix.h"
#include "../Components/RenderComponent.h"
#include "../Components/CameraComponent.h"

#include "VertexStream.h"
#include "VertexTypes/VertexPositionLayout.h"

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

            void ReceiveEvent(SDL_WindowEvent& windowEvent);
            void ToggleFullscreen();

            EffectPtr LoadEffect(const char* vertexShaderName, const char* fragmentShaderName);
            uint8_t LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount);
            uint8_t LoadMesh(const MeshPrimitiveBase& meshPrimitive);
            void SetCamera(CameraComponent* camera);

            RenderComponent* CreateRenderComponent(const IEntity& parent, uint8_t meshId) const;

            void LoadWireframeData(const IVertexType vertexData[], const uint indices[], const uint vertexCount);
            void ClearWireframe();

        private:

            void printError();

            void unloadEffects();
            void unloadMeshes();

            void renderWireframe();

            SDL_Window* createWindow();
            void resizeWindow(int w, int h);
            int _width = 1280;
            int _height = 720;
            
            SDL_Window* _window;
            SDL_Surface* _screenSurface;

            Context* _currentContext;
            EffectPtr _currentEffect;
            CameraComponent* _currentCamera;

            std::vector<EffectPtr> _loadedEffects;
            std::vector<MeshPtr> _loadedMeshes;

            // Wireframe temp variables
            EffectPtr _wireframeEffect;
            VertexStream* _wireframe;
            VertexPositionLayout* _wireframeLayout;

    };
}