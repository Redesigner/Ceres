#include "PhysicsService.h"

#include "../Components/PhysicsComponent.h"
#include "../Physics/Primitives/CubePrimitive.h"

#include <stdexcept>
#include <fmt/core.h>

namespace Ceres
{
    PhysicsService::PhysicsService()
    {}

    PhysicsService::~PhysicsService()
    {}

    ComponentRef PhysicsService::GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args)
    {
        if (typeName == "PhysicsComponent")
        {
            if (argCount == 0)
            {
                _components.Insert(new PhysicsComponent(parent, new CubePrimitive(1)));
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

    void PhysicsService::Update(float deltaSeconds)
    {
        for (IComponent* component : _components)
        {
            PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(component);
            
            Vector3 newPosition = physicsComponent->GetPosition() + physicsComponent->Velocity * deltaSeconds;
            physicsComponent->SetPosition(newPosition);
        }
    }
}