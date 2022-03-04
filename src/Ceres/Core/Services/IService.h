#pragma once

#include "../Components/Base/ComponentRef.h"
#include "../Components/Base/ComponentParameters.h"

#include <memory>
#include <string>

namespace Ceres
{
    using Type = std::type_index;
    using ComponentPR = std::unique_ptr<ComponentParams>;

    /// Handles creation and deletion of Components, implmenting special logic when necessary.
    class IService
    {
        public:
            IService();
            virtual ~IService();

            // TODO: Provide base implementation and exception handling so that
            // derived classes only need to provide argument count and type name
            virtual ComponentRef GenerateComponent(Type type, ComponentPR& params) = 0;
            virtual ComponentRef GetComponent(unsigned int id);

        protected:
            ComponentList _components;
    };
}