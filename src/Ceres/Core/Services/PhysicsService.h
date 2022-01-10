#pragma once

#include "IService.h"
#include "../Components/PhysicsComponent.h"

namespace Ceres
{
    class PhysicsService : public IService
    {
        public:
            PhysicsService();
            ~PhysicsService();

            virtual ComponentRef GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args) override;
            void Update(float deltaSeconds);

        private:
            void stepComponent(PhysicsComponent* host, float seconds);
            std::vector<PhysicsComponent*> _getComponentsWithinDistance(PhysicsComponent* sourceComponent, const float distance);
    };
}