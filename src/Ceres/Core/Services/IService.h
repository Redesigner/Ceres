#pragma once

#include "../Components/Base/ComponentPtr.h"
#include "../Components/Base/ComponentParameters.h"

#include <memory>
#include <string>

namespace Ceres
{
    using Type = std::type_index;
    using TypeList = std::vector<Type>;
    using ComponentPR = std::unique_ptr<ComponentParams>;

    /// Handles creation and deletion of Components, implmenting special logic when necessary.
    /// Wraps around functions that Components might need to call.
    class IService
    {
        public:
            IService();
            virtual ~IService();

            virtual ComponentPtrBase GenerateComponent(Type type, ComponentPR& params) = 0;
            virtual ComponentPtrBase GetComponent(unsigned int id);
            virtual TypeList GetAssociatedTypes() const = 0;

        protected:
            ComponentList _components;
    };
}