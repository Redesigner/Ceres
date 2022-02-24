#include "Block.h"

#include "../Services/RenderService.h"
#include "../Services/PhysicsService.h"
#include "../Physics/Primitives/CubePrimitive.h"

namespace Ceres
{
    Block::Block(ServiceContainer& serviceContainer, float x, float y, float z, AssetPtr<Mesh> mesh)
    {
        _primitive = new CubePrimitive(1);
        GENERATE_COMPONENT(RenderService, "RenderComponent", (mesh));
        GENERATE_COMPONENT(PhysicsService, "PhysicsComponent", (_primitive));

        SendMessage(Message::Write<Vector3>("Scale", &Vector3(x, y, z)));
        SendMessage(Message::Write<Vector3>("Position", &Vector3(-2.0f, 0, 0)));
    }
    
    Block::~Block()
    {
        delete _primitive;
    }
}