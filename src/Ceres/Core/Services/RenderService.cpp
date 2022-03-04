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

    ComponentRef RenderService::GenerateComponent(Type type, ComponentPR& params)
    {
        if(type == Type(typeid(RenderComponent)))
        {
            switch(params->Count())
            {
                case 1:
                {
                    AssetPtr<Mesh> mesh = params->Get<AssetPtr<Mesh>>(0);
                    return _parentDevice.CreateRenderComponent(mesh);
                }
                case 2:
                {
                    AssetPtr<Mesh> mesh = params->Get<AssetPtr<Mesh>>(0);
                    AssetPtr<Texture> texture = params->Get<AssetPtr<Texture>>(1);
                    return _parentDevice.CreateRenderComponent(mesh, texture);
                }
                default:
                {
                    throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type.name()));
                }
            }
        }
        else if(type == Type(typeid(CameraComponent)))
        {
            if(params->Count() == 0)
            {
                CameraComponent* camera = new CameraComponent();
                _components.Insert(camera);
                // TODO: Set camera properly, rather than setting it each time we create one.
                _parentDevice.SetCamera(camera);
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type.name()));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", type.name()));
        }
    }
}