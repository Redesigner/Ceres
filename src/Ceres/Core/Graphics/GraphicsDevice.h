#pragma once

#include <memory>
#include <vector>

#include "Cubemap.h"
#include "Mesh.h"
#include "Shadowmap.h"
#include "Skybox.h"
#include "Sprite.h"
#include "Texture.h"
#include "Window.h"

#include "Primitives/MeshPrimitive.h"
#include "VertexTypes/IVertexType.h"

#include "../Common/AssetPointer.h"
#include "../Common/Matrix.h"

#include "../Components/Base/ComponentRef.h"
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

            void ReceiveEvent(SDL_WindowEvent& windowEvent);
            void ToggleFullscreen();

            AssetPtr<Effect> LoadEffect(const char* vertexShaderName, const char* fragmentShaderName);
            AssetPtr<Effect> LoadEffect(const char* shaderName);
            AssetPtr<Mesh> LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount, AssetPtr<Effect> effect);
            AssetPtr<Mesh> LoadMesh(const MeshPrimitiveBase& meshPrimitive, AssetPtr<Effect> effect);
            AssetPtr<Mesh> LoadMesh(const MeshPrimitiveBase& meshPrimitive);
            AssetPtr<Texture> LoadTexture(std::string textureName);

            void SetCamera(ComponentRef<CameraComponent> camera);

            ComponentRefBase CreateRenderComponent(AssetPtr<Mesh> mesh);
            ComponentRefBase CreateRenderComponent(AssetPtr<Mesh> mesh, AssetPtr<Texture> texture);

            ComponentRefBase CreateCamera();

        private:
            void render(RenderComponent* renderComponent) const;
            void prerender(RenderComponent* renderComponent) const;

            void printError();

            void unloadEffects();
            void unloadMeshes();
            void unloadTextures();

            void renderSkybox();

            ComponentList _renderComponents;
            ComponentList _cameraComponents;

            Window _window;
            Context* _currentContext;
            ComponentRef<CameraComponent> _currentCamera;

            std::vector<Effect>     _loadedEffects;
            std::vector<Mesh>       _loadedMeshes;
            std::vector<Texture>    _loadedTextures;

            Skybox* _skybox;
            Cubemap* _skyboxCubemap;
            Shadowmap* _shadowmap;

            AssetPtr<Effect> _skyboxEffect;
            AssetPtr<Effect> _spriteEffect;

            Cubemap* _lightMap;

            Sprite* _sprite;
            AssetPtr<Texture> _spriteTexture;
    };
}