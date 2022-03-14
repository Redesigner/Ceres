#ifndef ACTORSERVICE_H
#define ACTORSERVICE_H

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

            virtual ComponentPtrBase GenerateComponent(Type type, ComponentPR& params) override;
            virtual TypeList GetAssociatedTypes() const override;

            void Update(double seconds);

        private:
    };
}

#endif // ACTORSERVICE_H
