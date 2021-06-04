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

    bool IEntity::SendMessage(int message)
    {
        bool handled = false;
        for(IComponent& component : _components)
        {
            if(component.recieveMessage())
            {
                handled = true;
            }
        }
        message += 1;
        return handled;
    }
}