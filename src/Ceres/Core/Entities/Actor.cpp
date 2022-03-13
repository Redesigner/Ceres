#include "Actor.h"

#include "../Components/CameraComponent.h"
#include "../Components/ControllerComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/SpriteComponent.h"

#include "../Physics/Primitives/CubePrimitive.h"
#include "../Physics/Primitives/SpherePrimitive.h"

namespace Ceres
{
    Actor::Actor(ServiceContainer& serviceContainer, AssetPtr<Ceres::Mesh> mesh, AssetPtr<Ceres::Texture> texture)
        :IEntity(serviceContainer)
    {
        _primitive.reset(dynamic_cast<IPrimitive*>(new CubePrimitive(0.5f, 0.5f, 1.6f)));
        AddComponent<MeshComponent>(ComponentParams::WriteParams(mesh, texture));
        AddComponent<CameraComponent>();
        AddComponent<ControllerComponent>();
        AddComponent<PhysicsComponent>(ComponentParams::WriteParams(_primitive));
        AddComponent<MovementComponent>();
        AddComponent<SpriteComponent>(ComponentParams::WriteParams(texture, 64, 64, 64, 64));

        SendMessage("Pause");
        SendMessage("Position", Vector3::Zero() );
    }

    Actor::~Actor()
    {
    }
}