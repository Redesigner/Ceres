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

    ComponentPtrBase RenderService::GenerateComponent(Type type, ComponentPR& params)
    {
        if(type == Type(typeid(MeshComponent)))
        {
            switch(params->Count())
            {
                case 1:
                {
                    AssetPtr<Mesh> mesh = params->Get<AssetPtr<Mesh>>(0);
                    return _parentDevice.CreateMeshComponent(mesh);
                }
                case 2:
                {
                    AssetPtr<Mesh> mesh = params->Get<AssetPtr<Mesh>>(0);
                    AssetPtr<Texture> texture = params->Get<AssetPtr<Texture>>(1);
                    return _parentDevice.CreateMeshComponent(mesh, texture);
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
                return _parentDevice.CreateCamera();
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type.name()));
            }
        }
        else if(type == Type(typeid(SpriteComponent)))
        {
            if(params->Count() == 5)
            {
                return _parentDevice.CreateSprite(params->Get<AssetPtr<Texture>>(0), params->Get<int>(1), params->Get<int>(2), params->Get<int>(3), params->Get<int>(4));
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type.name()));
            }
        }
        else if(type == Type(typeid(TextComponent)))
        {
            if(params->Count() == 4)
            {
                return _parentDevice.CreateText(params->Get<std::string>(0), params->Get<std::string>(3), params->Get<int>(1), params->Get<int>(2));
            }
        }
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", type.name()));
        }
    }

    TypeList RenderService::GetAssociatedTypes() const
    {
        return TypeList{Type(typeid(MeshComponent)), Type(typeid(CameraComponent)), Type(typeid(SpriteComponent)), Type(typeid(TextComponent))};
    }

    AssetPtr<Texture> RenderService::GetTexture(std::string textureName)
    {
        return _parentDevice.GetTexture(textureName);
    }
    AssetPtr<Effect> RenderService::GetEffect(std::string effectName)
    {
        return _parentDevice.GetEffect(effectName);
    }
    AssetPtr<Mesh> RenderService::GetMesh(std::string meshName)
    {
        return _parentDevice.GetMesh(meshName);
    }
}