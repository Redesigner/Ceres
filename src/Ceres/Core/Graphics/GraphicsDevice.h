#pragma once

#include <memory>
#include <vector>

#include "CubeMap.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Texture.h"
#include "Window.h"

#include "Primitives/MeshPrimitive.h"
#include "VertexTypes/IVertexType.h"

#include "../Common/AssetPointer.h"
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

            AssetPtr<Effect> LoadEffect(const char* vertexShaderName, const char* fragmentShaderName);
            AssetPtr<Effect> LoadEffect(const char* shaderName);
            AssetPtr<Mesh> LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount, AssetPtr<Effect> effect);
            AssetPtr<Mesh> LoadMesh(const MeshPrimitiveBase& meshPrimitive, AssetPtr<Effect> effect);
            AssetPtr<Mesh> LoadMesh(const MeshPrimitiveBase& meshPrimitive);
            AssetPtr<Texture> LoadTexture(std::string textureName);

            void SetCamera(CameraComponent* camera);

            // TODO: Add parameter pack type?
            RenderComponent* CreateRenderComponent(const IEntity& parent, AssetPtr<Mesh> mesh) const;
            RenderComponent* CreateRenderComponent(const IEntity& parent, AssetPtr<Mesh> mesh, AssetPtr<Texture> texture) const;

        private:

            void printError();

            void unloadEffects();
            void unloadMeshes();
            void unloadTextures();

            void renderSkybox();

            Window _window;
            Context* _currentContext;
            CameraComponent* _currentCamera;

            std::vector<Effect>     _loadedEffects;
            std::vector<Mesh>       _loadedMeshes;
            std::vector<Texture>    _loadedTextures;

            Skybox* _skybox;
            CubeMap* _skyboxCubeMap;
            AssetPtr<Effect> _skyboxEffect;
    };
}