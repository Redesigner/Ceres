#include "RenderComponent.h"

namespace Ceres
{
    RenderComponent::RenderComponent(const IEntity& parent, uint8_t meshId)
        :IComponent(parent), MeshId(meshId), Transform()
    {}

    RenderComponent::~RenderComponent()
    {}

}