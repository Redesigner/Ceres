#include "RenderService.h"

#include "../Components/CameraComponent.h"
#include "../Graphics/VertexTypes/VertexPosition.h"

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

    ComponentRef RenderService::GenerateComponent(std::string type, const IEntity& parent, ComponentPR& params)
    {
        if(type == "RenderComponent")
        {
            switch(params->Count())
            {
                case 1:
                {
                    AssetPtr<Mesh> mesh = params->Get<AssetPtr<Mesh>>(0);
                    RenderComponent* renderComponent = _parentDevice.CreateRenderComponent(parent, mesh);
                    _components.Insert(renderComponent);
                    return ComponentRef(&_components, _components.Size() - 1);
                }
                case 2:
                {
                    AssetPtr<Mesh> mesh = params->Get<AssetPtr<Mesh>>(0);
                    AssetPtr<Texture> texture = params->Get<AssetPtr<Texture>>(1);
                    RenderComponent* renderComponent = _parentDevice.CreateRenderComponent(parent, mesh, texture);
                    _components.Insert(renderComponent);
                    return ComponentRef(&_components, _components.Size() - 1);
                }
                default:
                {
                    throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type));
                }
            }
        }
        else if(type == "CameraComponent")
        {
            if(params->Count() == 0)
            {
                CameraComponent* camera = new CameraComponent(parent);
                _components.Insert(camera);
                // TODO: Set camera properly, rather than setting it each time we create one.
                _parentDevice.SetCamera(camera);
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", type));
        }
    }

    void RenderService::CreatePacked(ComponentParams& params)
    {

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
}