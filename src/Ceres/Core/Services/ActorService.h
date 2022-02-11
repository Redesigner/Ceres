#pragma once

#include "IService.h"
#include "../Components/Base/ComponentList.h"

namespace Ceres
{
    /// A service/factory for components that don't necessarily belong to other services
    /// essentially handles creation and cleanup, and nothing else
    class ActorService : public IService
    {
        public:
            ActorService();
            ~ActorService();

            virtual ComponentRef GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args) override;
            void Update(double seconds);

        private:
    };
}