#include "GraphicsDevice.h"

#include "Context.h"
#include "Effect.h"
#include "Mesh.h"
#include "../Entities/IEntity.h"

#include <stdexcept>
#include <fmt/core.h>

extern "C" 
{
	#include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

namespace Ceres
{
    GraphicsDevice::GraphicsDevice()
        : _defaultModelMatrix(Matrix::Identity())
    {
        _window = createWindow();
        _currentContext = new Context(_window);
        _screenSurface = nullptr;
        _currentEffect = LoadEffect("Shaders\\defaultVertex.GLSL", "Shaders\\defaultFragment.GLSL");
        _defaultModelMatrix = Matrix::Identity();
    }

    GraphicsDevice::~GraphicsDevice()
    {
        unloadEffects();
        unloadMeshes();
        delete _currentContext;
        if(_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
    }

    void GraphicsDevice::Render()
    {
        _defaultModelMatrix = _defaultModelMatrix * Matrix::RotationAlongY(0.0001f);
        beginRender();
        MeshPtr componentMesh = _loadedMeshes[0];
        for(const RenderComponent& renderComponent : _renderComponents)
        {
            _currentEffect->Begin();
            // GLint location = glGetUniformLocation(0, "model");
            // glUniformMatrix4fv(1, 1, GL_FALSE, renderComponent.Transform.GetMatrix().M[0] );
            _currentEffect->SetMatrix("model", renderComponent.Transform.GetMatrix());
            componentMesh = _loadedMeshes[renderComponent.MeshId];
            componentMesh->GetVertexArray().Bind();
            glDrawElements(GL_TRIANGLES, componentMesh->Size(), GL_UNSIGNED_INT, NULL);

        }
        endRender();
    }

    EffectPtr GraphicsDevice::LoadEffect(const char* vertexShaderName, const char* fragmentShaderName)
    {
        EffectPtr effect = EffectPtr(new Effect(vertexShaderName, fragmentShaderName));
        _loadedEffects.push_back(effect);
        return effect;
    }

    uint8_t GraphicsDevice::LoadMesh(IVertexType vertexData[], const IVertexLayout& vertexLayout, int vertexCount, unsigned int indices[], int indexCount)
    {
        MeshPtr mesh = MeshPtr(new Mesh(vertexData, vertexLayout, vertexCount, indices, indexCount, _currentEffect));
        _loadedMeshes.push_back(mesh);
        return (uint8_t) (_loadedMeshes.size() - 1);
    }

    RenderComponent& GraphicsDevice::CreateRenderComponent(uint8_t meshId)
    {
        return _renderComponents.emplace_back(IEntity(), meshId);
    }


    void GraphicsDevice::beginRender()
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
    }

    void GraphicsDevice::endRender()
    {
        SDL_GL_SwapWindow(_window);
        printError();
    }

    void GraphicsDevice::printError()
    {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            fmt::print("OpenGL error: {}\n", gluErrorString(err));
        }
    }

    SDL_Window* GraphicsDevice::createWindow()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) { return false; }
        return SDL_CreateWindow("Ceres",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    }

    void GraphicsDevice::unloadEffects()
    {
        _loadedEffects.clear();
    }

    void GraphicsDevice::unloadMeshes()
    {
        _loadedMeshes.clear();
    }
}