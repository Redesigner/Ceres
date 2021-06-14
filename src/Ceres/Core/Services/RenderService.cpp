#include "RenderService.h"

#include <exception>
#include <fmt/core.h>

namespace Ceres
{
    RenderService::RenderService(const GraphicsDevice& graphicsDevice)
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
                _components.Insert(_parentDevice.CreateRenderComponent(parent, meshId));
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
            _parentDevice.Render((RenderComponent*) _components[i]);
        }
    }
}