#include "Actor.h"

#include "../Services/RenderService.h"
#include "../Services/InputService.h"
#include "../Services/PhysicsService.h"

namespace Ceres
{
    Actor::Actor(ServiceContainer& serviceContainer)
    {
        uint8_t meshId = 0;
        ComponentRef mesh = serviceContainer.GetService<RenderService>()->GenerateComponent("RenderComponent", *this, 1, &meshId);
        ComponentRef camera = serviceContainer.GetService<RenderService>()->GenerateComponent("CameraComponent", *this, 0, nullptr);
        ComponentRef controller = serviceContainer.GetService<InputService>()->GenerateComponent("ControllerComponent", *this, 0, nullptr);
        ComponentRef physics = serviceContainer.GetService<PhysicsService>()->GenerateComponent("PhysicsComponent", *this, 0, nullptr);
        _components = {mesh, camera, controller, physics};
    }

    Actor::~Actor()
    {}
}