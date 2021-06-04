#include "IComponent.h"

namespace Ceres
{
    IComponent::IComponent(const IEntity& parent)
        :parent(parent)
    {}

    IComponent::~IComponent()
    {}

    bool IComponent::recieveMessage()
    {
        return false;
    }
}