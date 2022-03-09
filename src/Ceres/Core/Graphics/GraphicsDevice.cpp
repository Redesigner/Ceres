#include "GraphicsDevice.h"

#include "Context.h"
#include "Effect.h"
#include "Mesh.h"
#include "../Entities/Base/IEntity.h"

#include <stdexcept>
#include <fmt/core.h>

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
    GraphicsDevice::GraphicsDevice()
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
        
        AssetPtr<Effect> defaultEffect = LoadEffect("default");
        _skyboxEffect = LoadEffect("skybox");

        _skybox = new Skybox();
        std::string cubeMapLocation = CONTENT_DIR + "Textures\\skybox\\";
        _skyboxCubemap = new Cubemap(cubeMapLocation.c_str()); 
        _skyboxEffect->SetTexture("skybox", _skyboxCubemap);

        _shadowmap = new Shadowmap(1024, LoadEffect("shadowmap"));
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
        renderSkybox();

        glCullFace(GL_FRONT);
        _shadowmap->SetPosition(_currentCamera->GetPosition());
        _shadowmap->Bind();
        for (IComponent* component : _renderComponents)
        {
            RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component);
            prerender(renderComponent);
        }
        glCullFace(GL_BACK);
        _shadowmap->Unbind();
        _window.ResizeViewport();


        for (IComponent* component : _renderComponents)
        {
            RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component);
            render(renderComponent);
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
            }
        }
    }

    void GraphicsDevice::ToggleFullscreen()
    {
        _window.ToggleFullscreen();
    }
    

    AssetPtr<Effect> GraphicsDevice::LoadEffect(const char* vertexShaderName, const char* fragmentShaderName)
    {
        _loadedEffects.push_back(std::move(Effect(vertexShaderName, fragmentShaderName)));
        // set the ambient lightmap here, since it shouldn't change once we load the effect
        _loadedEffects.at(_loadedEffects.size() - 1).SetCubemap("lightmap", _lightMap);
        return AssetPtr<Effect>(_loadedEffects, _loadedEffects.size() - 1);
    }
    AssetPtr<Effect> GraphicsDevice::LoadEffect(const char* shaderName)
    {
        std::string vertexName = SHADER_PATH + shaderName + VERT_EXTENSION;
        std::string fragmentName = SHADER_PATH + shaderName + FRAG_EXTENSTION;
        return LoadEffect(vertexName.c_str(), fragmentName.c_str());
    }

    AssetPtr<Mesh> GraphicsDevice::LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], uint indexCount, AssetPtr<Effect> effect)
    {
        _loadedMeshes.push_back(std::move(Mesh(vertexData, vertexLayout, vertexCount, indices, indexCount, effect)));
        return AssetPtr<Mesh>(_loadedMeshes, _loadedMeshes.size() - 1);
    }
    AssetPtr<Mesh> GraphicsDevice::LoadMesh(const MeshPrimitiveBase& meshPrimitive, AssetPtr<Effect> effect)
    {
        return LoadMesh(meshPrimitive.GetVertices(), *meshPrimitive.GetVertexLayout(), meshPrimitive.GetVertexCount(), meshPrimitive.GetIndices(), meshPrimitive.GetIndexCount(), effect);
    }
    AssetPtr<Mesh> GraphicsDevice::LoadMesh(const MeshPrimitiveBase& meshPrimitive)
    {
        return LoadMesh(meshPrimitive, AssetPtr<Effect>(_loadedEffects, 0));
    }

    AssetPtr<Texture> GraphicsDevice::LoadTexture(std::string textureName)
    {
        std::string texturePath = CONTENT_DIR + "Textures\\" + textureName;
        _loadedTextures.push_back(std::move(Texture(texturePath)));
        return AssetPtr<Texture>(_loadedTextures, _loadedTextures.size() - 1);
    }

    void GraphicsDevice::SetCamera(ComponentRef<CameraComponent> camera)
    {
        _currentCamera = camera;
    }



    ComponentRefBase GraphicsDevice::CreateRenderComponent(AssetPtr<Mesh> mesh)
    {
       _renderComponents.Insert(new RenderComponent(mesh));
       return ComponentRefBase(&_renderComponents, _renderComponents.Size() - 1);
    }

    ComponentRefBase GraphicsDevice::CreateRenderComponent(AssetPtr<Mesh> mesh, AssetPtr<Texture> texture)
    {
        _renderComponents.Insert(new RenderComponent(mesh, texture));
        return ComponentRefBase(&_renderComponents, _renderComponents.Size() - 1);
    }

    ComponentRefBase GraphicsDevice::CreateCamera()
    {
        _cameraComponents.Insert(new CameraComponent());
        _currentCamera = ComponentRef<CameraComponent>(&_cameraComponents, _cameraComponents.Size() - 1);
        _currentCamera->SetClipRange(0.1f, 100.0f);
        const Vector2 resolution = _window.GetViewportSize();
        _currentCamera->SetResolution(resolution.X, resolution.Y);
        _currentCamera->SetFOV(90.0f);
        return _currentCamera;
    }


    // Private methods
    void GraphicsDevice::render(RenderComponent* renderComponent) const
    {
        Mesh& componentMesh = *renderComponent->Mesh;
        Effect& componentEffect = *componentMesh.GetEffect();
        componentMesh.GetVertexArray().Bind();
        componentMesh.GetIndexBuffer().Bind();

        componentEffect.Begin();
        componentEffect.SetViewMatrix(_currentCamera->GetMatrix());
        componentEffect.SetVector3("cameraPos", _currentCamera->GetPosition());
        componentEffect.SetMatrix("model", renderComponent->Transform.GetMatrix());
        componentEffect.SetMatrix("lightSpace", _shadowmap->GetMatrix());
        if (renderComponent->Texture)
        {
            componentEffect.SetTexture("surfaceTexture", renderComponent->Texture);
        }
        componentEffect.SetShadowmap(_shadowmap);
        glDrawElements(GL_TRIANGLES, componentMesh.Size(), GL_UNSIGNED_INT, NULL);
    }

    void GraphicsDevice::prerender(RenderComponent* renderComponent) const
    {
        Mesh& componentMesh = *renderComponent->Mesh;
        componentMesh.GetVertexArray().Bind();
        componentMesh.GetIndexBuffer().Bind();
        // Render component to the shadow map
        _shadowmap->SetModelMatrix(renderComponent->Transform.GetMatrix());
        glDrawElements(GL_TRIANGLES, componentMesh.Size(), GL_UNSIGNED_INT, NULL);

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

    void GraphicsDevice::renderSkybox()
    {
        // glCullFace(GL_FRONT);
        glDepthMask(GL_FALSE);
        _skybox->GetVertexArray().Bind();
        _skybox->GetIndexBuffer().Bind();

        _skyboxEffect->Begin();
        _skyboxEffect->SetViewMatrix(_currentCamera->GetRotationMatrix());
        _skyboxEffect->SetTexture("skybox", _skyboxCubemap);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
        glDepthMask(GL_TRUE);
    }
}