#pragma once

#include "../../Components/Base/IComponent.h"
#include "../../Components/Base/ComponentParameters.h"
#include "../../Components/Base/ComponentRef.h"
#include "../../Components/Base/Message.h"

#include "../../Services/ServiceContainer.h"

#include <vector>
    
namespace Ceres
{
    class IEntity
    {
        public:
            IEntity(ServiceContainer& serviceContainer);
            ~IEntity();

            // TODO: move to protected once testing is done
            bool SendMessage(Message* Message) const;
            
            template <typename T>
            void AddComponent(std::unique_ptr<ComponentParams> &params)
            {
                ComponentRef component = _serviceContainer.CreateComponent<T>(params);
                component->SetParent(this);
                _components.emplace_back(component);
            }

            template <typename T>
            void AddComponent()
            {
                ComponentRef component = _serviceContainer.CreateComponent<T>(ComponentParams::Empty());
                component->SetParent(this);
                _components.emplace_back(component);
            }


        private:
            uint8_t _identifier;
            ServiceContainer& _serviceContainer;

        protected:
            /// Returns true if message is recieved by a component, otherwise returns false.

            std::vector<ComponentRef> _components;
    };
}