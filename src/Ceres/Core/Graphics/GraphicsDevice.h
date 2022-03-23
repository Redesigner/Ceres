#pragma once

#include <memory>
#include <vector>

#include "Cubemap.h"
#include "FontBatcher.h"
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
#include "../Components/TextComponent.h"

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
            // Create a shader program without using lights... won't be used for much later, just works in the current uniform setup
            AssetPtr<Effect> LoadSimpleEffect(const char* vertexShaderName, const char* fragmentShaderName, const char* shaderName);
            AssetPtr<Effect> LoadSimpleEffect(const char* shaderName);
            AssetPtr<Effect> GetEffect(std:: string effectName);

            AssetPtr<Mesh> LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], const uint indexCount, AssetPtr<Effect> effect, std::string name);
            AssetPtr<Mesh> LoadMesh(const MeshPrimitiveBase& meshPrimitive, AssetPtr<Effect> effect, std::string name);
            AssetPtr<Mesh> LoadMesh(const MeshPrimitiveBase& meshPrimitive, std::string name);
            AssetPtr<Mesh> GetMesh(std::string meshName);

            AssetPtr<Texture> LoadTexture(std::string fileName, std::string textureName);
            AssetPtr<Texture> LoadTexture(std::string textureName);
            AssetPtr<Texture> GetTexture(std::string textureName);

            void LoadFont(std::string fontName);


            void SetCamera(ComponentPtr<CameraComponent> camera);

            ComponentPtrBase CreateMeshComponent(AssetPtr<Mesh> mesh);
            ComponentPtrBase CreateMeshComponent(AssetPtr<Mesh> mesh, AssetPtr<Texture> texture);

            ComponentPtrBase CreateCamera();

            ComponentPtrBase CreateSprite(AssetPtr<Texture> texture, int x, int y, int w, int h);

            ComponentPtrBase CreateText(std::string fontID, std::string text, int x, int y);

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
            void renderText();

            void printPrefix() const;

            ContentManager& _contentManager;

            // TODO: allocate memory more effeciently and use a different container?
            ComponentList _cameraComponents;
            ComponentList _meshComponents;
            ComponentList _spriteComponents;
            ComponentList _textComponents;

            Window _window;
            Context* _currentContext;
            ComponentPtr<CameraComponent> _currentCamera;

            // Should these be held by content manager instead???
            std::vector<Effect>         _loadedEffects;
            std::vector<Mesh>           _loadedMeshes;
            std::vector<Texture>        _loadedTextures;
            std::vector<FontBatcher>    _fontBatchers;

            // TODO: have content manager handle this map?
            std::unordered_map<std::string, AssetPtr<FontBatcher>> _fontIDMap;

            Skybox* _skybox;
            Cubemap* _skyboxCubemap;
            Shadowmap* _shadowmap;

            AssetPtr<Effect> _skyboxEffect;
            AssetPtr<Effect> _spriteEffect;
            AssetPtr<Effect> _fontEffect;


            Cubemap* _lightMap;

            Plane* _spritePlane;
    };
}