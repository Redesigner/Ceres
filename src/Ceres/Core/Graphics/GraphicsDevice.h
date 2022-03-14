#pragma once

#include <memory>
#include <vector>

#include "Cubemap.h"
#include "Mesh.h"
#include "Shadowmap.h"
#include "Skybox.h"
#include "Plane.h"
#include "Texture.h"
#include "Window.h"

#include "Primitives/MeshPrimitive.h"
#include "VertexTypes/IVertexType.h"

#include "../Common/AssetPointer.h"
#include "../Common/Matrix.h"

#include "../Components/Base/ComponentPtr.h"
#include "../Components/CameraComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/SpriteComponent.h"

#include "../IO/ContentManager.h"

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

            GraphicsDevice(ContentManager& contentManager);
            ~GraphicsDevice();

            void BeginRender();
            void EndRender();

            void Render();

            void ReceiveEvent(SDL_WindowEvent& windowEvent);
            void ToggleFullscreen();

            void LockWindow();
            void UnlockWindow();

            AssetPtr<Effect> LoadEffect(const char* vertexShaderName, const char* fragmentShaderName, const char* shaderName);
            AssetPtr<Effect> LoadEffect(const char* shaderName);
            AssetPtr<Effect> GetEffect(std:: string effectName);

            AssetPtr<Mesh> LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount, AssetPtr<Effect> effect, std::string name);
            AssetPtr<Mesh> LoadMesh(const MeshPrimitiveBase& meshPrimitive, AssetPtr<Effect> effect, std::string name);
            AssetPtr<Mesh> LoadMesh(const MeshPrimitiveBase& meshPrimitive, std::string name);
            AssetPtr<Mesh> GetMesh(std::string meshName);

            AssetPtr<Texture> LoadTexture(std::string fileName, std::string textureName);
            AssetPtr<Texture> LoadTexture(std::string textureName);
            AssetPtr<Texture> GetTexture(std::string textureName);

            void SetCamera(ComponentRef<CameraComponent> camera);

            ComponentPtrBase CreateMeshComponent(AssetPtr<Mesh> mesh);
            ComponentPtrBase CreateMeshComponent(AssetPtr<Mesh> mesh, AssetPtr<Texture> texture);

            ComponentPtrBase CreateCamera();

            ComponentPtrBase CreateSprite(AssetPtr<Texture> texture, int x, int y, int w, int h);

        private:
            void render(MeshComponent& meshComponent) const;
            void prerender(MeshComponent& meshComponent) const;

            void render(SpriteComponent& spriteComponent);

            void printError();

            void unloadEffects();
            void unloadMeshes();
            void unloadTextures();

            void renderMeshes();
            void renderSkybox();
            void renderShadows();
            void renderSprites();

            ContentManager& _contentManager;

            ComponentList _meshComponents;
            ComponentList _cameraComponents;
            ComponentList _spriteComponents;

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

            Plane* _spritePlane;
    };
}