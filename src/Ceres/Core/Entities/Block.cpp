#include "Block.h"

#include "../Services/RenderService.h"

namespace Ceres
{
    Block::Block(ServiceContainer& serviceContainer, float x, float y, float z)
    {
        uint8_t meshId = 0;
        ComponentRef mesh = serviceContainer.GetService<RenderService>()->GenerateComponent("RenderComponent", *this, 1, &meshId);
        _components = {mesh};

        Vector3 scale = Vector3(x, y, z);
        SendMessage(Message::Write<Vector3>("Scale", &scale));
    }
    
    Block::~Block()
    {}
}