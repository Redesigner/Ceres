#include "Block.h"

#include "../Components/RenderComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Physics/Primitives/CubePrimitive.h"

namespace Ceres
{
    Block::Block(ServiceContainer& serviceContainer, float x, float y, float z, AssetPtr<Mesh> mesh)
        :IEntity(serviceContainer)
    {
        _primitive.reset(dynamic_cast<IPrimitive*>(new CubePrimitive(1)));
        AddComponent<RenderComponent>(ComponentParams::WriteParams(mesh));
        AddComponent<PhysicsComponent>(ComponentParams::WriteParams(_primitive));

        SendMessage("Scale", Vector3(x, y, z));
    }

    Block::Block(ServiceContainer& serviceContainer, float x, float y, float z, AssetPtr<Mesh> mesh, AssetPtr<Texture> texture)
        :IEntity(serviceContainer)
    {
        _primitive.reset(dynamic_cast<IPrimitive*>(new CubePrimitive(1)));
        AddComponent<RenderComponent>(ComponentParams::WriteParams(mesh, texture));
        AddComponent<PhysicsComponent>(ComponentParams::WriteParams(_primitive));

        SendMessage("Scale", Vector3(x, y, z));
    }
    
    Block::~Block()
    {
    }
}