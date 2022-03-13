#pragma once

#include "Message.h"

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
        public:
            IComponent(const std::type_index typeIndex);
            ~IComponent();
            
            /** 
             * @brief Handle a message sent by another component. Returns true if the message can be handled by this component, otherwise, returns false.
             */
            virtual bool ReceiveMessage(Message& message) = 0;

            template <typename T>
            bool TypeOf() { return _typeIndex == std::type_index(typeid(T)); }
            /**
             * @brief Set the parent entity. This is *NOT* the owner of the component
             */
            void SetParent(IEntity* parent);

        private:
            const IEntity* _parent;
            const std::type_index _typeIndex;

        protected:
            bool sendMessage(Message& message) const;
    };
}