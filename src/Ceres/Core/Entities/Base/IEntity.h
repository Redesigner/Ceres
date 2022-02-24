#pragma once

#include "../../Components/Base/IComponent.h"
#include "../../Components/Base/ComponentParameters.h"
#include "../../Components/Base/ComponentRef.h"
#include "../../Components/Base/Message.h"

#include <vector>

#define GENERATE_COMPONENT(ServiceName, ComponentTypeName, Params) \
    _components.push_back(serviceContainer.GetService<ServiceName>()->GenerateComponent(ComponentTypeName, *this, ComponentParams::WriteParams Params ))
#define GENERATE_COMPONENT_NOPARAMS(ServiceName, ComponentTypeName) \
    _components.push_back(serviceContainer.GetService<ServiceName>()->GenerateComponent(ComponentTypeName, *this, ComponentParams::Empty()))

    
namespace Ceres
{
    class IEntity
    {
        public:
            IEntity();
            ~IEntity();

            // TODO: move to protected once testing is done
            bool SendMessage(Message* Message) const;

        private:
            uint8_t _identifier;

        protected:
            /// Returns true if message is recieved by a component, otherwise returns false.

            std::vector<ComponentRef> _components;

    };
}