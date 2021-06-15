#include "IComponent.h"

namespace Ceres
{
    IComponent::IComponent(const IEntity& parent)
        :_parent(parent)
    {}

    IComponent::~IComponent()
    {}
}