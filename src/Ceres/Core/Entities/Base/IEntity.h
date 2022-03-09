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
            IEntity(const IEntity&) = delete;
            IEntity(IEntity&&);
            ~IEntity();

            IEntity& operator =(const IEntity&) = delete;
            IEntity& operator =(IEntity&& entity) noexcept;

            template <typename T>
            bool SendMessage(std::string type, T value) const
            {
                return SendMessage(Message::Write(type, value));
            }

            bool SendMessage(std::string type) const;
            bool SendMessage(Message& Message) const;
            
            template <typename T>
            void AddComponent(std::unique_ptr<ComponentParams> &params)
            {
                ComponentRefBase component = _serviceContainer.CreateComponent<T>(params);
                component->SetParent(this);
                _components.emplace_back(component);
            }

            template <typename T>
            void AddComponent()
            {
                ComponentRefBase component = _serviceContainer.CreateComponent<T>(ComponentParams::Empty());
                component->SetParent(this);
                _components.emplace_back(component);
            }


        private:
            uint8_t _identifier;
            ServiceContainer& _serviceContainer;

        protected:
            /// Returns true if message is recieved by a component, otherwise returns false.

            std::vector<ComponentRefBase> _components;
    };
}