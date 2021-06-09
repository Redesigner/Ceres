#pragma once

#include "../Components/IComponent.h"
#include "../Components/ComponentRef.h"
#include "../Components/Message.h"

#include <vector>

namespace Ceres
{
    class IEntity
    {
        public:
            IEntity();
            ~IEntity();

            // TODO: move to protected once testing is done
            bool SendMessage(Message* Message);

        private:
            uint8_t _identifier;

        protected:
            /// Returns true if message is recieved by a component, otherwise returns false.

            std::vector<ComponentRef> _components;

    };
}