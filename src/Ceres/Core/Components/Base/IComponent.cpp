#include "IComponent.h"

#include "../../Entities/Base/IEntity.h"

namespace Ceres
{
    IComponent::IComponent(const IEntity& parent, const std::type_index typeIndex)
        :_parent(parent), _typeIndex(typeIndex)
    {}

    IComponent::~IComponent()
    {}

    bool IComponent::sendMessage(Message* message) const
    {
        return _parent.SendMessage(message);
    }

}