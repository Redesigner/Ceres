#include "ActorService.h"

#include "../Components/MovementComponent.h"
#include <fmt/core.h>

namespace Ceres
{
    ActorService::ActorService()
    {}

    ActorService::~ActorService()
    {}

    ComponentRef ActorService::GenerateComponent(std::string type, const IEntity& parent, ComponentPR& params)
    {
        if (type == "MovementComponent")
        {
            if (params->Count() == 0)
            {
                _components.Insert(new MovementComponent(parent));
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", type));
        }
    }

}