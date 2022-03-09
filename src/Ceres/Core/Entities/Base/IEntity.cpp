#include "IEntity.h"

#include <vector>

namespace Ceres
{
    IEntity::IEntity(ServiceContainer& serviceContainer)
        :_serviceContainer(serviceContainer)
    {}

    IEntity::IEntity(IEntity&& entity)
        :_serviceContainer(entity._serviceContainer)
    {
        _components = std::vector<ComponentRefBase>(entity._components);
        for (ComponentRefBase component : _components)
        {
            component->SetParent(this);
        }
    }

    IEntity::~IEntity()
    {}

    IEntity& IEntity::operator=(IEntity&& entity) noexcept
    {
        _serviceContainer = entity._serviceContainer;
        _components = std::vector<ComponentRefBase>(entity._components);
        for (ComponentRefBase component : _components)
        {
            component->SetParent(this);
        }
        return *this;
    }

    bool IEntity::SendMessage(std::string type) const
    {
        return SendMessage(Message::Write(type, 0));
    }

    bool IEntity::SendMessage(Message& message) const
    {
        bool handled = false;
        for(ComponentRefBase component : _components)
        {
            if(component->RecieveMessage(message))
            {
                handled = true;
            }
        }
        return handled;
    }
}