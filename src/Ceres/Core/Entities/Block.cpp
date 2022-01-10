#include "Block.h"

#include "../Services/RenderService.h"
#include "../Services/PhysicsService.h"


namespace Ceres
{
    Block::Block(ServiceContainer& serviceContainer, float x, float y, float z)
    {
        uint8_t meshId = 0;
        ComponentRef mesh = serviceContainer.GetService<RenderService>()->GenerateComponent("RenderComponent", *this, 1, &meshId);
        ComponentRef physicsComponent = serviceContainer.GetService<PhysicsService>()->GenerateComponent("PhysicsComponent", *this, 0, nullptr);

        _components = {mesh, physicsComponent};

        SendMessage(Message::Write<Vector3>("Scale", &Vector3(x, y, z)));
        // SendMessage(Message::Write<Vector3>("Position", &Vector3(0, 0, -2.0f)));
    }
    
    Block::~Block()
    {}
}