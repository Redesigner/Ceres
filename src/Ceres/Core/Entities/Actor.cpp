#include "Actor.h"

#include "../Components/CameraComponent.h"
#include "../Components/ControllerComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/SpriteComponent.h"

#include "../Physics/Primitives/CubePrimitive.h"
#include "../Physics/Primitives/SpherePrimitive.h"

#include "../Services/RenderService.h"

namespace Ceres
{
    Actor::Actor(ServiceContainer& serviceContainer)
        :IEntity(serviceContainer)
    {
        AssetPtr<Mesh> meshPtr = serviceContainer.GetService<RenderService>()->GetMesh("dummy");
        AssetPtr<Texture> texturePtr = serviceContainer.GetService<RenderService>()->GetTexture("dummy");
        _primitive.reset(dynamic_cast<IPrimitive*>(new CubePrimitive(0.5f, 0.5f, 1.6f)));
        AddComponent<MeshComponent>(ComponentParams::WriteParams(meshPtr, texturePtr));
        AddComponent<CameraComponent>();
        AddComponent<ControllerComponent>();
        AddComponent<PhysicsComponent>(ComponentParams::WriteParams(_primitive));
        AddComponent<MovementComponent>();
        AddComponent<SpriteComponent>(ComponentParams::WriteParams(serviceContainer.GetService<RenderService>()->GetTexture("heart"), 64, 64, 64, 64));
        AddComponent<SpriteComponent>(ComponentParams::WriteParams(serviceContainer.GetService<RenderService>()->GetTexture("arialX"), 128, 64, 64, 64));

        SendMessage("Pause");
        SendMessage("Position", Vector3::Zero() );
    }

    Actor::~Actor()
    {
    }
}