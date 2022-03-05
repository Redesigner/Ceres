#include "IComponent.h"

#include "../../Entities/Base/IEntity.h"

#include <fmt/core.h>

namespace Ceres
{
    IComponent::IComponent(const std::type_index typeIndex)
        :_typeIndex(typeIndex)
    {}

    IComponent::~IComponent()
    {}

    void IComponent::SetParent(IEntity* parent)
    {
        if (parent)
        {
            _parent = parent;
        }
    }

    bool IComponent::sendMessage(Message& message) const
    {
        if (!_parent)
        {
            fmt::print("[component] tried to send a message, but the component doesn't have a parent.\n");
        }
        return _parent->SendMessage(message);
    }

}