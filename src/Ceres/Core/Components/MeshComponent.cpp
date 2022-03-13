#include "MeshComponent.h"

namespace Ceres
{
    MeshComponent::MeshComponent(AssetPtr<Ceres::Mesh> mesh)
        :IComponent(std::type_index(typeid(MeshComponent))), Mesh(mesh), Transform(), Texture()
    {}

    MeshComponent::MeshComponent(AssetPtr<Ceres::Mesh> mesh, AssetPtr<Ceres::Texture> texture)
            :IComponent(std::type_index(typeid(MeshComponent))), Mesh(mesh), Transform(), Texture(texture)
    {}

    MeshComponent::~MeshComponent()
    {}

    bool MeshComponent::ReceiveMessage(Message& message)
    {
        if(message.Type == "Translate")
        {
            Vector3 position = message.GetData<Vector3>();
            Transform.SetPosition(Transform.GetPosition() + position);
            return true;
        }
        else if (message.Type == "Position")
        {
            const Vector3 position = message.GetData<Vector3>();
            Transform.SetPosition(position);
        }
        else if(message.Type == "Scale")
        {
            Vector3 scale = message.GetData<Vector3>();
            Transform.SetScale(scale);
            return true;
        }
        else if(message.Type == "Rotate")
        {
            Transform.SetRotation(Transform.GetRotation() + message.GetData<Vector3>());
            return true;
        }
        else if(message.Type == "RotateMesh")
        {
            Transform.SetRotation(Transform.GetRotation() + message.GetData<Vector3>());
            return true;
        }
        return false;
    }

}