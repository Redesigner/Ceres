#include "Actor.h"

#include "../Services/RenderService.h"
#include "../Services/InputService.h"

namespace Ceres
{
    Actor::Actor(ServiceContainer& serviceContainer)
    {
        uint8_t meshId = 0;
        ComponentRef mesh = serviceContainer.GetService<RenderService>()->GenerateComponent("RenderComponent", *this, 1, &meshId);
        ComponentRef controller = serviceContainer.GetService<InputService>()->GenerateComponent("ControllerComponent", *this, 0, nullptr);
        _components = {mesh};
    }

    Actor::~Actor()
    {}
}