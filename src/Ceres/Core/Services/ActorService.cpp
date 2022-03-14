#include "ActorService.h"

#include "../Components/MovementComponent.h"
#include <fmt/core.h>

namespace Ceres
{
    ActorService::ActorService()
    {}

    ActorService::~ActorService()
    {}

    ComponentPtrBase ActorService::GenerateComponent(Type type, ComponentPR& params)
    {
        if (type == Type(typeid(MovementComponent)))
        {
            if (params->Count() == 0)
            {
                _components.Insert(new MovementComponent());
                return ComponentPtrBase(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type.name()));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", type.name()));
        }
    }

    TypeList ActorService::GetAssociatedTypes() const
    {
        return TypeList{Type(typeid(MovementComponent))};
    }
}