#pragma once

#include "MessageSystem/Message.h"
#include "MessageSystem/MessageSystem.h"

#include <functional>
#include <typeindex>

namespace Ceres
{
    class IEntity;

    /**
     * @brief The base component type. Components are usually created and owned by a service.
     * 
     */
    class IComponent
    {
        using MessageHandler = std::function<void()>;
        public:
            IComponent(const std::type_index typeIndex);
            virtual ~IComponent();
            
            /** 
             * @brief Handle a message sent by another component. Returns true if the message can be handled by this component, otherwise, returns false.
             */
            bool ReceiveMessage(Message& message);

            template <typename T>
            bool TypeOf() { return _typeIndex == std::type_index(typeid(T)); }
            /**
             * @brief Set the parent entity. This is *NOT* the owner of the component
             */
            void SetParent(IEntity* parent);

        private:
            const IEntity* _parent = nullptr;
            const std::type_index _typeIndex;

        protected:
            bool sendMessage(Message& message) const;
            void addMessageHandler(std::string messageType, std::function<void(IComponent* component, Message& message)> handler);
    };
}