#pragma once

#include "IService.h"
#include "../Components/PhysicsComponent.h"

namespace Ceres
{
    class RenderService;
    class PhysicsService : public IService
    {
        public:
            PhysicsService();
            PhysicsService(RenderService* debugRenderer);
            ~PhysicsService();

            virtual ComponentPtrBase GenerateComponent(Type type, ComponentPR& params) override;
            virtual TypeList GetAssociatedTypes() const override;

            void Update(float deltaSeconds);

        private:
            void stepComponent(PhysicsComponent* host, float seconds, int iteration);
            void stepComponent(PhysicsComponent* host, float seconds);
            std::vector<PhysicsComponent*> getComponentsWithinDistance(PhysicsComponent* sourceComponent, const float distance);
            RenderService* _debugRenderer;
    };
}