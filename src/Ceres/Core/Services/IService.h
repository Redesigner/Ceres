#pragma once

#include "../Components/Base/ComponentPtr.h"
#include "../Components/Base/ComponentParameters.h"

#include <memory>
#include <string>

namespace Ceres
{
    using Type = std::type_index;
    using ComponentPR = std::unique_ptr<ComponentParams>;

    /// Handles creation and deletion of Components, implmenting special logic when necessary.
    /// Wraps around functions that Components might need to call.
    class IService
    {
        public:
            IService();
            virtual ~IService();

            // TODO: Provide base implementation and exception handling so that
            // derived classes only need to provide argument count and type name
            virtual ComponentPtrBase GenerateComponent(Type type, ComponentPR& params) = 0;
            virtual ComponentPtrBase GetComponent(unsigned int id);

        protected:
            ComponentList _components;
    };
}