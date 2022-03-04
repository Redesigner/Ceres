#include "Block.h"

#include "../Components/RenderComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Physics/Primitives/CubePrimitive.h"

namespace Ceres
{
    Block::Block(ServiceContainer& serviceContainer, float x, float y, float z, AssetPtr<Mesh> mesh)
        :IEntity(serviceContainer)
    {
        _primitive = new CubePrimitive(1);
        AddComponent<RenderComponent>(ComponentParams::WriteParams(mesh));
        AddComponent<PhysicsComponent>(ComponentParams::WriteParams(_primitive));

        SendMessage(Message::Write<Vector3>("Scale", &Vector3(x, y, z)));
        SendMessage(Message::Write<Vector3>("Position", &Vector3(-2.0f, 0, 0)));
    }
    
    Block::~Block()
    {
        delete _primitive;
    }
}