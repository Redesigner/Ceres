#include "GraphicsDevice.h"

#include "Context.h"
#include "Effect.h"
#include "Mesh.h"
#include "../Entities/Base/IEntity.h"
#include "../Common/Matrix2D.h"

#include <stdexcept>
#include <fmt/core.h>
#include <fmt/color.h>

extern "C" 
{
	#include <SDL2/SDL.h>
    #include "SDL_image.h"
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

const std::string CWD = SDL_GetBasePath();
const std::string CONTENT_DIR = CWD + "..\\..\\content\\";
const std::string SHADER_PATH = "\\Shaders\\";
const std::string VERT_EXTENSION = ".vert.glsl";
const std::string FRAG_EXTENSTION = ".frag.glsl";

void GLAPIENTRY
MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fmt::print("GL CALLBACK: {} type = {}, severity = {}, message = {}\n", ( type == GL_DEBUG_TYPE_ERROR ? "[GL ERROR]" : "" ), type, severity, message );
}

namespace Ceres
{
    GraphicsDevice::GraphicsDevice(ContentManager& contentManager)
        :_contentManager(contentManager)
    {
        _currentContext = new Context(_window);

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Load our ambient lightmap before we setup our shaders, so we can bind it on creation
        std::string lightMapLocation = CONTENT_DIR + "Textures\\lightmap\\ambient_";
        _lightMap = new Cubemap(lightMapLocation.c_str());
        
        LoadEffect("default");
        _skyboxEffect = LoadEffect("skybox");
        _spriteEffect = LoadEffect("sprite");

        _skybox = new Skybox();
        std::string cubeMapLocation = CONTENT_DIR + "Textures\\skybox\\";
        _skyboxCubemap = new Cubemap(cubeMapLocation.c_str()); 
        _skyboxEffect->SetTexture("skybox", _skyboxCubemap);

        _shadowmap = new Shadowmap(2048, LoadEffect("shadowmap"));
        _spritePlane = new Plane();

        _fontBatchers.emplace_back(128, _contentManager.LoadFont("arial.ttf", 128), LoadEffect("font"));
        _fontBatchers[0].LoadString("This is a test message!", 256, 64);
    }

    GraphicsDevice::~GraphicsDevice()
    {
        unloadEffects();
        unloadMeshes();
        delete _currentContext;
        delete _skybox;

        delete _skyboxCubemap;
        delete _lightMap;
        delete _shadowmap;
        delete _spritePlane;
    }

    // This method is called by the Program object, which abstracts it away from
    // our Game object. It will always/only be called on the start of a frame.
    void GraphicsDevice::BeginRender()
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
    }

    // This method is called by the Program object, which abstracts it away from
    // our Game object. It will always/only be called on the end of a frame,
    // after any logic in Game.Render() has been executed.
    void GraphicsDevice::EndRender()
    {
        _window.SwapBuffer();
    }

    void GraphicsDevice::Render()
    {
        renderShadows();
        renderMeshes();
        renderSkybox();
        renderSprites();
        for (int i = 0; i < _fontBatchers.size(); i++)
        {
            _fontBatchers[i].Bind();
            glDrawElements(GL_TRIANGLES, _fontBatchers[i].GetTriCount(), GL_UNSIGNED_INT, NULL);
        }
    }

    void GraphicsDevice::ReceiveEvent(SDL_WindowEvent& windowEvent)
    {
        switch(windowEvent.event)
        {
            default:
            {
                return;
            }
            case SDL_WINDOWEVENT_RESIZED:
            {
                _window.Resize(windowEvent.data1, windowEvent.data2);
                return;
            }
            case SDL_WINDOWEVENT_MAXIMIZED:
            {
                _window.Maximize();
                return;
            }
        }
    }

    void GraphicsDevice::ToggleFullscreen()
    {
        _window.ToggleFullscreen();
    }
    
    void GraphicsDevice::LockWindow()
    {
        _window.Lock();
    }
    void GraphicsDevice::UnlockWindow()
    {
        _window.Unlock();
    }

    AssetPtr<Effect> GraphicsDevice::LoadEffect(const char* vertexShaderName, const char* fragmentShaderName, const char* shaderName)
    {
        const std::string& vertexShaderSource = _contentManager.LoadString(vertexShaderName);
        const std::string& fragmentShaderSource = _contentManager.LoadString(fragmentShaderName);
        _loadedEffects.push_back(std::move(Effect(vertexShaderSource, fragmentShaderSource, shaderName)));
        
        // set the ambient lightmap here, since it shouldn't change once we load the effect
        _loadedEffects.at(_loadedEffects.size() - 1).SetCubemap("lightmap", _lightMap);
        return AssetPtr<Effect>(_loadedEffects, _loadedEffects.size() - 1);
    }
    AssetPtr<Effect> GraphicsDevice::LoadEffect(const char* shaderName)
    {
        std::string vertexName = SHADER_PATH + shaderName + VERT_EXTENSION;
        std::string fragmentName = SHADER_PATH + shaderName + FRAG_EXTENSTION;
        return LoadEffect(vertexName.c_str(), fragmentName.c_str(), shaderName);
    }
    AssetPtr<Effect> GraphicsDevice::GetEffect(std::string effectName)
    {
        for (int i = 0; i < _loadedEffects.size(); i++)
        {
            if (_loadedEffects[i].GetName() == effectName)
            {
                return AssetPtr<Effect>(_loadedEffects, i);
            }
        }
        printPrefix();
        fmt::print("Unable to find effect: '{}'.\n", effectName);
        return AssetPtr<Effect>();
    }


    AssetPtr<Mesh> GraphicsDevice::LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], uint indexCount, AssetPtr<Effect> effect, std::string name)
    {
        _loadedMeshes.push_back(std::move(Mesh(vertexData, vertexLayout, vertexCount, indices, indexCount, effect, name)));
        return AssetPtr<Mesh>(_loadedMeshes, _loadedMeshes.size() - 1);
    }
    AssetPtr<Mesh> GraphicsDevice::LoadMesh(const MeshPrimitiveBase& meshPrimitive, AssetPtr<Effect> effect, std::string name)
    {
        return LoadMesh(meshPrimitive.GetVertices(), *meshPrimitive.GetVertexLayout(), meshPrimitive.GetVertexCount(), meshPrimitive.GetIndices(), meshPrimitive.GetIndexCount(), effect, name);
    }
    AssetPtr<Mesh> GraphicsDevice::LoadMesh(const MeshPrimitiveBase& meshPrimitive, std::string name)
    {
        return LoadMesh(meshPrimitive, AssetPtr<Effect>(_loadedEffects, 0), name);
    }
    AssetPtr<Mesh> GraphicsDevice::GetMesh(std::string meshName)
    {
        for (int i = 0; i < _loadedMeshes.size(); i++)
        {
            if (_loadedMeshes[i].GetName() == meshName)
            {
                return AssetPtr<Mesh>(_loadedMeshes, i);
            }
        }
        printPrefix();
        fmt::print("Unable to find mesh: '{}'.\n", meshName);
        return AssetPtr<Mesh>();
    }


    AssetPtr<Texture> GraphicsDevice::LoadTexture(std::string fileName, std::string textureName)
    {
        std::string texturePath = CONTENT_DIR + "Textures\\" + fileName;
        _loadedTextures.push_back(std::move(Texture(texturePath, textureName)));
        return AssetPtr<Texture>(_loadedTextures, _loadedTextures.size() - 1);
    }

    AssetPtr<Texture> GraphicsDevice::LoadTexture(std::string textureName)
    {
        std::string texturePath = CONTENT_DIR + "Textures\\" + textureName;
        _loadedTextures.push_back(std::move(Texture(texturePath, textureName)));
        return AssetPtr<Texture>(_loadedTextures, _loadedTextures.size() - 1);
    }

    AssetPtr<Texture> GraphicsDevice::GetTexture(std::string textureName)
    {
        for (int i = 0; i < _loadedTextures.size(); i++)
        {
            if (_loadedTextures[i].GetName() == textureName)
            {
                return AssetPtr<Texture>(_loadedTextures, i);
            }
        }
        printPrefix();
        fmt::print("Unable to find texture: '{}'.\n", textureName);
        return AssetPtr<Texture>();
    }

    void GraphicsDevice::SetCamera(ComponentRef<CameraComponent> camera)
    {
        _currentCamera = camera;
    }


    // ======== Component creation methods ========
    ComponentPtrBase GraphicsDevice::CreateMeshComponent(AssetPtr<Mesh> mesh)
    {
       _meshComponents.Insert(new MeshComponent(mesh));
       return ComponentPtrBase(&_meshComponents, _meshComponents.Size() - 1);
    }

    ComponentPtrBase GraphicsDevice::CreateMeshComponent(AssetPtr<Mesh> mesh, AssetPtr<Texture> texture)
    {
        _meshComponents.Insert(new MeshComponent(mesh, texture));
        return ComponentPtrBase(&_meshComponents, _meshComponents.Size() - 1);
    }

    ComponentPtrBase GraphicsDevice::CreateCamera()
    {
        _cameraComponents.Insert(new CameraComponent());
        _currentCamera = ComponentRef<CameraComponent>(&_cameraComponents, _cameraComponents.Size() - 1);
        _currentCamera->SetClipRange(1.0f, 10.0f);
        const Vector2 resolution = _window.GetViewportSize();
        _currentCamera->SetResolution(resolution.X, resolution.Y);
        _currentCamera->SetFOV(90.0f);
        return _currentCamera;
    }

    ComponentPtrBase GraphicsDevice::CreateSprite(AssetPtr<Texture> texture, int x, int y, int w, int h)
    {
        _spriteComponents.Insert(new SpriteComponent(texture, x, y, w, h));
        return ComponentPtrBase(&_spriteComponents, _spriteComponents.Size() - 1);
    }


    // ======== Instanced rendering methods ========
    void GraphicsDevice::render(MeshComponent& meshComponent) const
    {
        Mesh& componentMesh = *(meshComponent.Mesh);
        Effect& componentEffect = *componentMesh.GetEffect();
        componentMesh.GetVertexArray().Bind();
        componentMesh.GetIndexBuffer().Bind();

        componentEffect.Begin();
        componentEffect.SetViewMatrix(_currentCamera->GetMatrix());
        componentEffect.SetVector3("cameraPos", _currentCamera->GetPosition());
        componentEffect.SetMatrix("model", meshComponent.Transform.GetMatrix());
        componentEffect.SetMatrix("lightSpace", _shadowmap->GetMatrix());
        if (meshComponent.Texture)
        {
            componentEffect.SetTexture("surfaceTexture", meshComponent.Texture);
        }
        componentEffect.SetShadowmap(_shadowmap);
        glDrawElements(GL_TRIANGLES, componentMesh.Size(), GL_UNSIGNED_INT, NULL);
    }

    void GraphicsDevice::prerender(MeshComponent& meshComponent) const
    {
        Mesh& componentMesh = *(meshComponent.Mesh);
        componentMesh.GetVertexArray().Bind();
        componentMesh.GetIndexBuffer().Bind();
        _shadowmap->SetModelMatrix(meshComponent.Transform.GetMatrix());
        glDrawElements(GL_TRIANGLES, componentMesh.Size(), GL_UNSIGNED_INT, NULL);
    }

    void GraphicsDevice::render(SpriteComponent& spriteComponent)
    {
        if (!spriteComponent.Texture)
        {
            return;
        }
        _spriteEffect->SetTexture("tex", spriteComponent.Texture);
        Vector2 windowSize = _window.GetViewportSize();
        _spriteEffect->SetMatrix2D("transform", Matrix2D::Sprite(
            spriteComponent.Position.X, spriteComponent.Position.Y,
            spriteComponent.Size.X, spriteComponent.Size.Y,
            windowSize.X, windowSize.Y));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    }

    void GraphicsDevice::printError()
    {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            fmt::print("OpenGL error: {}\n", gluErrorString(err));
        }
    }

    void GraphicsDevice::unloadEffects()
    {
        _loadedEffects.clear();
    }

    void GraphicsDevice::unloadMeshes()
    {
        _loadedMeshes.clear();
    }

    void GraphicsDevice::unloadTextures()
    {
        _loadedTextures.clear();
    }

    // ======== Render methods ========
    void GraphicsDevice::renderMeshes()
    {
        for (IComponent* component : _meshComponents)
        {
            MeshComponent* meshComponent = dynamic_cast<MeshComponent*>(component);
            render(*meshComponent);
        }
    }

    void GraphicsDevice::renderSkybox()
    {
        glDepthFunc(GL_LEQUAL);
        _skybox->GetVertexArray().Bind();
        _skybox->GetIndexBuffer().Bind();

        _skyboxEffect->Begin();
        _skyboxEffect->SetViewMatrix(_currentCamera->GetRotationMatrix());
        _skyboxEffect->SetTexture("skybox", _skyboxCubemap);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);        
        glDepthFunc(GL_LESS);
    }

    void GraphicsDevice::renderShadows()
    {
        glCullFace(GL_FRONT);
        _shadowmap->SetPosition(_currentCamera->GetPosition());
        _shadowmap->Bind();
        for (IComponent* component : _meshComponents)
        {
            MeshComponent* meshComponent = dynamic_cast<MeshComponent*>(component);
            prerender(*meshComponent);
        }
        glCullFace(GL_BACK);
        _shadowmap->Unbind();
        _window.ResizeViewport();

    }

    void GraphicsDevice::renderSprites()
    {
        _spriteEffect->Begin();
        _spritePlane->GetVertexArray().Bind();
        _spritePlane->GetIndexBuffer().Bind();
        for (IComponent* component : _spriteComponents)
        {
            SpriteComponent* spriteComponent = dynamic_cast<SpriteComponent*>(component);
            render(*spriteComponent);
        }
    }

    void GraphicsDevice::printPrefix() const
    {
        fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "[GraphicsDevice] ");
    }
}