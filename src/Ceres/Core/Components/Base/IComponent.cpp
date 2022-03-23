#include "IComponent.h"

#include "../../Entities/Base/IEntity.h"

#include <fmt/core.h>

namespace Ceres
{
    IComponent::IComponent(const std::type_index typeIndex)
        :_typeIndex(typeIndex)
    {
        MessageSystem::RegisterComponent(typeIndex);
    }

    IComponent::~IComponent()
    {}

    void IComponent::SetParent(IEntity* parent)
    {
        if (parent)
        {
            _parent = parent;
        }
    }

    bool IComponent::ReceiveMessage(Message& message)
    {
        const MessageHandlerMap& messageHandlerMap = MessageSystem::GetHandler(_typeIndex);
        return messageHandlerMap.Invoke(this, message);
    }

    bool IComponent::sendMessage(Message& message) const
    {
        if (_parent)
        {
            return _parent->SendMessage(message);
        }
        fmt::print("[component] tried to send a message, but the component doesn't have a parent.\n");
        return false;
    }

    void IComponent::addMessageHandler(std::string messageType, std::function<void(IComponent*, Message&)> handler)
    {
        MessageSystem::RegisterHandler(messageType, _typeIndex, handler);
    }

}