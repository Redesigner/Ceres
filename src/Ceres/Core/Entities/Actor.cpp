#include "Actor.h"

#include "../Services/RenderService.h"
#include "../Services/InputService.h"
#include "../Services/PhysicsService.h"
#include "../Services/ActorService.h"

#include "../Physics/Primitives/CubePrimitive.h"
#include "../Physics/Primitives/SpherePrimitive.h"

namespace Ceres
{
    Actor::Actor(ServiceContainer& serviceContainer, AssetPtr<Ceres::Mesh> mesh, AssetPtr<Ceres::Texture> texture)
    {
        // _primitive = new SpherePrimitive(.25f);
        _primitive = new CubePrimitive(1.0f);
        GENERATE_COMPONENT(RenderService, "RenderComponent", (mesh, texture));
        GENERATE_COMPONENT_NOPARAMS(RenderService, "CameraComponent");
        GENERATE_COMPONENT_NOPARAMS(InputService, "ControllerComponent");
        GENERATE_COMPONENT(PhysicsService, "PhysicsComponent", (_primitive));
        GENERATE_COMPONENT_NOPARAMS(ActorService, "MovementComponent");

        SendMessage(Message::Write<void>("Pause", 0));

        SendMessage(Message::Write<Vector3>("Position", &Vector3::Zero() ));
    }

    Actor::~Actor()
    {
        delete _primitive;
    }
}