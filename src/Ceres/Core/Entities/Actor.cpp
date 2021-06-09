#include "Actor.h"

#include "../Services/RenderService.h"

namespace Ceres
{
    Actor::Actor(ServiceContainer& serviceContainer)
    {
        uint8_t meshId = 0;
        ComponentRef mesh = serviceContainer.GetService<RenderService>()->GenerateComponent("RenderComponent", *this, 1, &meshId);
        _components = {mesh};
    }

    Actor::~Actor()
    {}
}