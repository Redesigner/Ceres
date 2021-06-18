#pragma once

#include "Message.h"

#include <typeindex>

namespace Ceres
{
    class IEntity;

    class IComponent
    {
        public:
            IComponent(const IEntity& parent, const std::type_index typeIndex);
            ~IComponent();
            
            virtual bool RecieveMessage(Message* message) = 0;
            template <typename T>
            bool TypeOf()
            {
                return _typeIndex == std::type_index(typeid(T));
            }

        private:

        protected:
            const IEntity& _parent;
            const std::type_index _typeIndex;
    };
}