#include "Actor.h"

#include "../Services/RenderService.h"
#include "../Services/InputService.h"
#include "../Services/PhysicsService.h"
#include "../Services/ActorService.h"

#include "../Physics/Primitives/CubePrimitive.h"
#include "../Physics/Primitives/SpherePrimitive.h"

namespace Ceres
{
    Actor::Actor(ServiceContainer& serviceContainer)
    {
        uint8_t meshID = 1;
        // _primitive = new SpherePrimitive(.25f);
        _primitive = new CubePrimitive(1.0f);

        ComponentRef mesh = serviceContainer.GetService<RenderService>()->GenerateComponent("RenderComponent", *this, 2, &meshID);
        ComponentRef camera = serviceContainer.GetService<RenderService>()->GenerateComponent("CameraComponent", *this, 0, nullptr);
        ComponentRef controller = serviceContainer.GetService<InputService>()->GenerateComponent("ControllerComponent", *this, 0, nullptr);
        ComponentRef physics = serviceContainer.GetService<PhysicsService>()->GenerateComponent("PhysicsComponent", *this, 1, _primitive);
        ComponentRef movement = serviceContainer.GetService<ActorService>()->GenerateComponent("MovementComponent", *this, 0, nullptr);
        _components = {mesh, camera, controller, physics, movement};

        SendMessage(Message::Write<void>("Pause", 0));

        SendMessage(Message::Write<Vector3>("Position", &Vector3::Zero() ));
    }

    Actor::~Actor()
    {
        delete _primitive;
    }
}