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
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

namespace Ceres
{
    GraphicsDevice::GraphicsDevice()
    {
        // TODO: properly initalize cameracomponent?


        _window = createWindow();
        _currentContext = new Context(_window);
        _screenSurface = nullptr;

        // glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);

        _currentEffect = LoadEffect("Shaders\\defaultVertex.GLSL", "Shaders\\defaultFragment.GLSL");
        _loadedMeshes = std::vector<MeshPtr>();
        

        _wireframeEffect = LoadEffect("Shaders\\wireframeVertex.GLSL", "Shaders\\wireframeFragment.GLSL");
        _wireframeLayout = new VertexPositionLayout();
        _wireframe = new VertexStream(*_wireframeLayout, 64, _wireframeEffect);
    }

    GraphicsDevice::~GraphicsDevice()
    {
        unloadEffects();
        unloadMeshes();
        delete _currentContext;
        delete _wireframe;
        delete _wireframeLayout;
        if(_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
    }

    // This method is called by the Program object, which abstracts it away from
    // our Game object. It will always/only be called on the start of a frame.
    void GraphicsDevice::BeginRender()
    {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
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
        componentMesh->GetVertexArray().Bind();
        componentMesh->GetIndexBuffer().Bind();
        
        _currentEffect->Begin();
        _currentEffect->SetViewMatrix(_currentCamera->GetMatrix());
        _currentEffect->SetVector3("cameraPos", _currentCamera->GetPosition());
        _currentEffect->SetMatrix("model", renderComponent->Transform.GetMatrix());
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
    

    EffectPtr GraphicsDevice::LoadEffect(const char* vertexShaderName, const char* fragmentShaderName)
    {
        EffectPtr effect = EffectPtr(new Effect(vertexShaderName, fragmentShaderName));
        _loadedEffects.push_back(effect);
        return effect;
    }

    uint8_t GraphicsDevice::LoadMesh(const IVertexType vertexData[], const IVertexLayout& vertexLayout, const uint vertexCount, const uint indices[], uint indexCount)
    {
        MeshPtr mesh = MeshPtr(new Mesh(vertexData, vertexLayout, vertexCount, indices, indexCount, _currentEffect));
        _loadedMeshes.push_back(mesh);
        return static_cast<uint8_t>(_loadedMeshes.size() - 1);
    }
    uint8_t GraphicsDevice::LoadMesh(const MeshPrimitiveBase& meshPrimitive)
    {
        return LoadMesh(meshPrimitive.GetVertices(), *meshPrimitive.GetVertexLayout(), meshPrimitive.GetVertexCount(), meshPrimitive.GetIndices(), meshPrimitive.GetIndexCount());
    }

    void GraphicsDevice::SetCamera(CameraComponent* camera)
    {
        _currentCamera = camera;
    }

    RenderComponent* GraphicsDevice::CreateRenderComponent(const IEntity& parent, uint8_t meshId) const
    {
       return new RenderComponent(parent, meshId);
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

    void GraphicsDevice::renderWireframe()
    {
        if (_wireframe->Size() == 0) { return; }

        glDisable(GL_DEPTH_TEST);
        _wireframe->GetVertexArray().Bind();
        _wireframeEffect->Begin();
        _wireframeEffect->SetViewMatrix(_currentCamera->GetMatrix());
        glDrawElements(GL_LINES, _wireframe->Size(), GL_UNSIGNED_INT, NULL);
    }

    SDL_Window* GraphicsDevice::createWindow()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) { return false; }
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