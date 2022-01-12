#include "RenderService.h"

#include "../Components/CameraComponent.h"

#include <exception>
#include <fmt/core.h>

namespace Ceres
{
    RenderService::RenderService(GraphicsDevice& graphicsDevice)
        :_parentDevice(graphicsDevice)
    {}

    RenderService::~RenderService()
    {
    }

    ComponentRef RenderService::GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args)
    {
        if(typeName == "RenderComponent")
        {
            if(argCount == 1)
            {
                uint8_t meshId = *(uint8_t*) args;
                RenderComponent* renderComponent = _parentDevice.CreateRenderComponent(parent, meshId);
                _components.Insert(renderComponent);
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", typeName));
            }
        }
        else if(typeName == "CameraComponent")
        {
            if(argCount == 0)
            {
                CameraComponent* camera = new CameraComponent(parent);
                _components.Insert(camera);
                // TODO: Set camera properly, rather than setting it each time we create one.
                _parentDevice.SetCamera(camera);
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", typeName));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", typeName));
        }
    }

    void RenderService::RenderComponents()
    {
        for(int i = 0; i < _components.Size(); i++)
        {
            if(_components[i]->TypeOf<RenderComponent>())
            {
                _parentDevice.Render((RenderComponent*) _components[i]);
            }
        }
    }

    void RenderService::LoadWireframeData(const IVertexType vertexData[], const int indices[], const int vertexCount)
    {
        _parentDevice.LoadWireframeData(vertexData, indices, vertexCount);
    }

    void RenderService::ClearWireframe()
    {
        _parentDevice.ClearWireframe();
    }
}