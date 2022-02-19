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

void GLAPIENTRY
MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fmt::print("GL CALLBACK: {} type = {}, severity = {}, message = {}\n", ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message );
}
namespace Ceres
{
    GraphicsDevice::GraphicsDevice()
    {
        // TODO: properly initalize cameracomponent?

        _window = createWindow();
        _currentContext = new Context(_window);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);

        _loadedMeshes = std::vector<MeshPtr>();

        _currentEffect = LoadEffect("Shaders\\defaultVertex.GLSL", "Shaders\\defaultFragment.GLSL");
        _wireframeEffect = LoadEffect("Shaders\\wireframeVertex.GLSL", "Shaders\\wireframeFragment.GLSL");
        _skyboxEffect = LoadEffect("Shaders\\skyboxVertex.GLSL", "Shaders\\skyboxFragment.GLSL");

        _skybox = new Skybox();
        std::string cubeMapLocation = CONTENT_DIR + "Textures\\skybox\\";
        _skyboxCubeMap = new CubeMap(cubeMapLocation.c_str());
        _wireframeLayout = new VertexPositionLayout();
        _wireframe = new VertexStream(*_wireframeLayout, 64, _loadedEffects[_wireframeEffect]);
    }

    GraphicsDevice::~GraphicsDevice()
    {
        unloadEffects();
        unloadMeshes();
        delete _currentContext;
        delete _wireframe;
        delete _wireframeLayout;
        delete _skybox;
        delete _skyboxCubeMap;

        if(_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
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
        renderWireframe();
        SDL_GL_SwapWindow(_window);
        printError();
    }

    void GraphicsDevice::Render(RenderComponent* renderComponent) const
    {
        MeshPtr componentMesh = _loadedMeshes[renderComponent->MeshId];
        EffectPtr componentEffect = componentMesh->GetEffect();
        componentMesh->GetVertexArray().Bind();
        componentMesh->GetIndexBuffer().Bind();

        componentEffect->Begin();
        componentEffect->SetViewMatrix(_currentCamera->GetMatrix());
        componentEffect->SetVector3("cameraPos", _currentCamera->GetPosition());
        componentEffect->SetMatrix("model", renderComponent->Transform.GetMatrix());
        
        if (renderComponent->TextureId >= 0)
        {
            TexturePtr componentTexture = _loadedTextures[renderComponent->TextureId];
            componentEffect->SetSampler("texSampler", *componentTexture);
        }

        glDrawElements(GL_TRIANGLES, componentMesh->Size(), GL_UNSIGNED_INT, NULL);
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
                resizeWindow(windowEvent.data1, windowEvent.data2);
                return;
            }
            case SDL_WINDOWEVENT_MAXIMIZED:
            {
                SDL_MaximizeWindow(_window);
                int w, h;
                SDL_GetWindowSize(_window, &w, &h);
                resizeWindow(w, h);
            }
        }
    }

    void GraphicsDevice::ToggleFullscreen()
    {
        bool fullscreen = SDL_GetWindowFlags(_window) & SDL_WINDOW_FULLSCREEN;
        if (!fullscreen)
        {
            int displayIndex = SDL_GetWindowDisplayIndex(_window);
            SDL_DisplayMode displayMode;
            SDL_GetDesktopDisplayMode(displayIndex, &displayMode);
            SDL_SetWindowSize(_window, displayMode.w, displayMode.h);
            resizeWindow(displayMode.w, displayMode.h);
            SDL_SetWindowFullscreen(_window, true);
        }
        else
        {
            SDL_SetWindowFullscreen(_window, false);
            SDL_SetWindowSize(_window, _width, _height);
            resizeWindow(_width, _height);
        }
    }
    

    uint8_t GraphicsDevice::LoadEffect(const char* vertexShaderName, const char* fragmentShaderName)
    {
        EffectPtr effect = std::make_shared<Effect>(vertexShaderName, fragmentShaderName);
        _loadedEffects.push_back(std::move(effect));
        return static_cast<uint8_t>(_loadedEffects.size() - 1);
    }

    uint8_t GraphicsDevice::LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], uint indexCount, uint8_t effectID)
    {
        EffectPtr effect = _loadedEffects[effectID];
        MeshPtr mesh = std::make_shared<Mesh>(vertexData, vertexLayout, vertexCount, indices, indexCount, effect);
        _loadedMeshes.push_back(std::move(mesh));
        return static_cast<uint8_t>(_loadedMeshes.size() - 1);
    }

    uint8_t GraphicsDevice::LoadMesh(const MeshPrimitiveBase& meshPrimitive, uint8_t effectID)
    {
        return LoadMesh(meshPrimitive.GetVertices(), *meshPrimitive.GetVertexLayout(), meshPrimitive.GetVertexCount(), meshPrimitive.GetIndices(), meshPrimitive.GetIndexCount(), effectID);
    }

    uint8_t GraphicsDevice::LoadTexture(std::string textureName)
    {
        std::string texturePath = CONTENT_DIR + "Textures\\" + textureName;
        TexturePtr texture = std::make_shared<Texture>(texturePath.c_str());
        _loadedTextures.push_back(std::move(texture));
        return static_cast<uint8_t>(_loadedTextures.size() - 1);
    }

    void GraphicsDevice::SetCamera(CameraComponent* camera)
    {
        _currentCamera = camera;
    }

    RenderComponent* GraphicsDevice::CreateRenderComponent(const IEntity& parent, uint8_t meshId) const
    {
       return new RenderComponent(parent, meshId);
    }

    RenderComponent* GraphicsDevice::CreateRenderComponent(const IEntity& parent, uint8_t meshId, uint8_t texId) const
    {
       return new RenderComponent(parent, meshId, texId);
    }

    void GraphicsDevice::LoadWireframeData(const IVertexType vertexData[], const uint indices[], const uint vertexCount)
    {
        _wireframe->AddData(vertexData, indices, vertexCount);
    }

    void GraphicsDevice::ClearWireframe()
    {
        _wireframe->Clear();
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

    void GraphicsDevice::renderWireframe()
    {
        if (_wireframe->Size() == 0)
        {
            return;
        }
        EffectPtr effect = _loadedEffects[_wireframeEffect];
        glDisable(GL_DEPTH_TEST);
        _wireframe->GetVertexArray().Bind();
        effect->Begin();
        effect->SetViewMatrix(_currentCamera->GetMatrix());
        glDrawElements(GL_LINES, _wireframe->Size(), GL_UNSIGNED_INT, NULL);
    }

    void GraphicsDevice::renderSkybox()
    {
        // glCullFace(GL_FRONT);
        glDepthMask(GL_FALSE);
        EffectPtr effect = _loadedEffects[_skyboxEffect];
        _skybox->GetVertexArray().Bind();
        _skybox->GetIndexBuffer().Bind();

        effect->Begin();
        effect->SetViewMatrix(_currentCamera->GetRotationMatrix());
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
        glDepthMask(GL_TRUE);
        // glCullFace(GL_BACK);
    }

    SDL_Window* GraphicsDevice::createWindow()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            fmt::print("Failed to initialize SDL.\n");
            return false;
        }
        if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            fmt::print("Failed to initialize SDL_image.\n");
            return false;
        }
        const int multisampleBufferCount = 1;
        const int multisampleSampleCount = 4;
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, multisampleBufferCount);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisampleSampleCount);
        return SDL_CreateWindow("Ceres",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    }

    void GraphicsDevice::resizeWindow(int w, int h)
    {
        glViewport(0, 0, w, h);
        for (EffectPtr effect : _loadedEffects)
        {
            effect->SetFrustrum(Matrix::Perspective(w, h, 90, .1f, 100.f));
        }
        return;
    }
}