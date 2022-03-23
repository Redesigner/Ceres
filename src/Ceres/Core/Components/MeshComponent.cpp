#include "MeshComponent.h"

namespace Ceres
{
    MeshComponent::MeshComponent(AssetPtr<Ceres::Mesh> mesh, AssetPtr<Ceres::Texture> texture)
            :IComponent(std::type_index(typeid(MeshComponent))), Mesh(mesh), Transform(), Texture(texture)
    {
        addMessageHandler("Translate", [](IComponent* component, Message& message)
            {
                MeshComponent* mesh = static_cast<MeshComponent*>(component);
                Vector3 position = message.GetData<Vector3>();
                mesh->Transform.SetPosition(mesh->Transform.GetPosition() + position);
            });

        addMessageHandler("Position", [](IComponent* component, Message& message)
            {
                MeshComponent* mesh = static_cast<MeshComponent*>(component);
                mesh->Transform.SetPosition(message.GetData<Vector3>());
            });

        addMessageHandler("Scale", [](IComponent* component, Message& message)
            {
                MeshComponent* mesh = static_cast<MeshComponent*>(component);
                Vector3 scale = message.GetData<Vector3>();
                mesh->Transform.SetScale(scale);
            });

        addMessageHandler("Rotate", [](IComponent* component, Message& message)
            {
                MeshComponent* mesh = static_cast<MeshComponent*>(component);
                mesh->Transform.SetRotation(mesh->Transform.GetRotation() + message.GetData<Vector3>());
            });

        addMessageHandler("RotateMesh", [](IComponent* component, Message& message)
            {
                MeshComponent* mesh = static_cast<MeshComponent*>(component);
                mesh->Transform.SetRotation(mesh->Transform.GetRotation() + message.GetData<Vector3>());
            });
    }

    MeshComponent::MeshComponent(AssetPtr<Ceres::Mesh> mesh)
        :MeshComponent(mesh, AssetPtr<Ceres::Texture>())
    {}

    MeshComponent::~MeshComponent()
    {}
}