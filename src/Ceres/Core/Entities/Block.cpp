#include "Block.h"

#include "../Components/MeshComponent.h"
#include "../Components/PhysicsComponent.h"

#include "../Physics/Primitives/CubePrimitive.h"

#include "../Services/RenderService.h"

namespace Ceres
{
    Block::Block(ServiceContainer& serviceContainer, float x, float y, float z, std::string mesh)
        :IEntity(serviceContainer)
    {
        AssetPtr<Mesh> meshPtr = serviceContainer.GetService<RenderService>()->GetMesh(mesh);
        _primitive.reset(dynamic_cast<IPrimitive*>(new CubePrimitive(1)));
        AddComponent<MeshComponent>(ComponentParams::WriteParams(meshPtr));
        AddComponent<PhysicsComponent>(ComponentParams::WriteParams(_primitive));

        SendMessage("Scale", Vector3(x, y, z));
    }

    Block::Block(ServiceContainer& serviceContainer, float x, float y, float z, std::string mesh, std::string texture)
        :IEntity(serviceContainer)
    {
        AssetPtr<Mesh> meshPtr = serviceContainer.GetService<RenderService>()->GetMesh(mesh);
        AssetPtr<Texture> texturePtr = serviceContainer.GetService<RenderService>()->GetTexture(texture);

        _primitive.reset(dynamic_cast<IPrimitive*>(new CubePrimitive(1)));
        AddComponent<MeshComponent>(ComponentParams::WriteParams(meshPtr, texturePtr));
        AddComponent<PhysicsComponent>(ComponentParams::WriteParams(_primitive));

        SendMessage("Scale", Vector3(x, y, z));
    }
    
    Block::~Block()
    {
    }
}