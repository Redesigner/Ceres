#include "Actor.h"

#include "../Components/CameraComponent.h"
#include "../Components/ControllerComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/RenderComponent.h"
#include "../Components/PhysicsComponent.h"

#include "../Physics/Primitives/CubePrimitive.h"
#include "../Physics/Primitives/SpherePrimitive.h"

namespace Ceres
{
    Actor::Actor(ServiceContainer& serviceContainer, AssetPtr<Ceres::Mesh> mesh, AssetPtr<Ceres::Texture> texture)
        :IEntity(serviceContainer)
    {
        // _primitive = new SpherePrimitive(.25f);
        _primitive = new CubePrimitive(1.0f);
        AddComponent<RenderComponent>(ComponentParams::WriteParams(mesh, texture));
        AddComponent<CameraComponent>();
        AddComponent<ControllerComponent>();
        AddComponent<PhysicsComponent>(ComponentParams::WriteParams(_primitive));
        AddComponent<MovementComponent>();

        SendMessage(Message::Write<void>("Pause", 0));

        SendMessage(Message::Write<Vector3>("Position", &Vector3::Zero() ));
    }

    Actor::~Actor()
    {
        delete _primitive;
    }
}