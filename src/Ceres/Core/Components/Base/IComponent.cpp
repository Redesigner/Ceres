#include "IComponent.h"

namespace Ceres
{
    IComponent::IComponent(const IEntity& parent, const std::type_index typeIndex)
        :_parent(parent), _typeIndex(typeIndex)
    {}

    IComponent::~IComponent()
    {}

}