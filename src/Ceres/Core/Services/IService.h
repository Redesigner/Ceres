#pragma once

#include "../Components/Base/ComponentRef.h"

#include <string>
#include <vector>

namespace Ceres
{

    /// Handles creation and deletion of Components, implmenting special logic when necessary.
    class IService
    {
        public:
            IService();
            virtual ~IService();

            // TODO: Provide base implementation and exception handling so that
            // derived classes only need to provide argument count and type name
            virtual ComponentRef GenerateComponent(std::string type, const IEntity& parent, int argCount, void* args) = 0;
            virtual ComponentRef GetComponent(unsigned int id);

        protected:
            ComponentList _components;
    };
}