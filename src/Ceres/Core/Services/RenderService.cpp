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

    ComponentRefBase RenderService::GenerateComponent(Type type, ComponentPR& params)
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
            {;
                return _parentDevice.CreateCamera();
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