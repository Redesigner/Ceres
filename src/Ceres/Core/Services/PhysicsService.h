#pragma once

#include "IService.h"

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
            
    };
}