#include "ActorService.h"

#include "../Components/MovementComponent.h"
#include <fmt/core.h>

namespace Ceres
{
    ActorService::ActorService()
    {}

    ActorService::~ActorService()
    {}

    ComponentRef ActorService::GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args)
    {
        if (typeName == "MovementComponent")
        {
            if (argCount == 0)
            {
                _components.Insert(new MovementComponent(parent));
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", typeName));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", typeName));
        }
    }

}