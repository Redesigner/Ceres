#include "IEntity.h"

#include <vector>

namespace Ceres
{
    IEntity::IEntity()
    {

    }
    IEntity::~IEntity()
    {

    }

    bool IEntity::SendMessage(Message* message)
    {
        bool handled = false;
        for(IComponent& component : _components)
        {
            if(component.RecieveMessage(message))
            {
                handled = true;
            }
        }
        delete message;
        return handled;
    }
}