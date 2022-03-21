#include "Actor.h"

#include "../Components/CameraComponent.h"
#include "../Components/ControllerComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"

#include "../Physics/Primitives/CubePrimitive.h"
#include "../Physics/Primitives/SpherePrimitive.h"

#include "../Services/RenderService.h"

namespace Ceres
{
    Actor::Actor(ServiceContainer& serviceContainer)
        :IEntity(serviceContainer)
    {
        static std::string text = "This text was created by the player entity!";
        static std::string arialString = "arial";
        AssetPtr<Mesh> meshPtr = serviceContainer.GetService<RenderService>()->GetMesh("dummy");
        AssetPtr<Texture> texturePtr = serviceContainer.GetService<RenderService>()->GetTexture("dummy");
        _primitive.reset(dynamic_cast<IPrimitive*>(new CubePrimitive(0.5f, 0.5f, 1.6f)));
        AddComponent<MeshComponent>(ComponentParams::WriteParams(meshPtr, texturePtr));
        AddComponent<CameraComponent>();
        AddComponent<ControllerComponent>();
        AddComponent<PhysicsComponent>(ComponentParams::WriteParams(_primitive));
        AddComponent<MovementComponent>();
        AddComponent<SpriteComponent>(ComponentParams::WriteParams(serviceContainer.GetService<RenderService>()->GetTexture("heart"), 64, 64, 64, 64));
        AddComponent<TextComponent>(ComponentParams::WriteParams(arialString, 128, 96, text));

        SendMessage("Pause");
        SendMessage("Position", Vector3::Zero() );
    }

    Actor::~Actor()
    {
    }
}