#include "Block.h"

#include "../Services/RenderService.h"
#include "../Services/PhysicsService.h"
#include "../Physics/Primitives/CubePrimitive.h"

namespace Ceres
{
    Block::Block(ServiceContainer& serviceContainer, float x, float y, float z)
    {
        uint8_t meshId = 0;
        _primitive = new CubePrimitive(1);
        ComponentRef mesh = serviceContainer.GetService<RenderService>()->GenerateComponent("RenderComponent", *this, 1, &meshId);
        ComponentRef physicsComponent = serviceContainer.GetService<PhysicsService>()->GenerateComponent("PhysicsComponent", *this, 1, _primitive);

        _components = {mesh, physicsComponent};

        SendMessage(Message::Write<Vector3>("Scale", &Vector3(x, y, z)));
        SendMessage(Message::Write<Vector3>("Position", &Vector3(-2.0f, 0, 0)));
    }
    
    Block::~Block()
    {
        delete _primitive;
    }
}