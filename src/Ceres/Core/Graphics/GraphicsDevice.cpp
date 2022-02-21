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

void GLAPIENTRY
MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fmt::print("GL CALLBACK: {} type = {}, severity = {}, message = {}\n", ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message );
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
        LoadEffect("default");
        _skyboxEffect = LoadEffect("skybox");

        _skybox = new Skybox();
        std::string cubeMapLocation = CONTENT_DIR + "Textures\\skybox\\";
        _skyboxCubeMap = new CubeMap(cubeMapLocation.c_str());
    }

    GraphicsDevice::~GraphicsDevice()
    {
        unloadEffects();
        unloadMeshes();
        delete _currentContext;
        delete _skybox;
        delete _skyboxCubeMap;
    }

    // This method is called by the Program object, which abstracts it away from
    // our Game object. It will always/only be called on the start of a frame.
    void GraphicsDevice::BeginRender()
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        renderSkybox();
    }

    // This method is called by the Program object, which abstracts it away from
    // our Game object. It will always/only be called on the end of a frame,
    // after any logic in Game.Render() has been executed.
    void GraphicsDevice::EndRender()
    {
        _window.SwapBuffer();
    }

    void GraphicsDevice::Render(RenderComponent* renderComponent) const
    {
        Mesh& componentMesh = *renderComponent->Mesh;
        Effect& componentEffect = *componentMesh.GetEffect();
        componentMesh.GetVertexArray().Bind();
        componentMesh.GetIndexBuffer().Bind();

        componentEffect.Begin();
        componentEffect.SetViewMatrix(_currentCamera->GetMatrix());
        componentEffect.SetVector3("cameraPos", _currentCamera->GetPosition());
        componentEffect.SetMatrix("model", renderComponent->Transform.GetMatrix());
        
        /* if (renderComponent->Texture)
        {
            componentEffect->SetSampler("texSampler", renderComponent->Texture);
        } */

        glDrawElements(GL_TRIANGLES, componentMesh.Size(), GL_UNSIGNED_INT, NULL);
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
        return AssetPtr<Effect>(_loadedEffects, _loadedEffects.size() - 1);
    }
    AssetPtr<Effect> GraphicsDevice::LoadEffect(const char* shaderName)
    {
        std::string vertexName = SHADER_PATH + shaderName + "Vertex.GLSL";
        std::string fragmentName = SHADER_PATH + shaderName + "Fragment.GLSL";
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

    void GraphicsDevice::SetCamera(CameraComponent* camera)
    {
        _currentCamera = camera;
    }

    RenderComponent* GraphicsDevice::CreateRenderComponent(const IEntity& parent, AssetPtr<Mesh> mesh) const
    {
       return new RenderComponent(parent, mesh);
    }

    RenderComponent* GraphicsDevice::CreateRenderComponent(const IEntity& parent, AssetPtr<Mesh> mesh, AssetPtr<Texture> texture) const
    {
       return new RenderComponent(parent, mesh, texture);
    }


    // Private methods

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
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
        glDepthMask(GL_TRUE);
        // glCullFace(GL_BACK);
    }
}