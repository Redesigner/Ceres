#pragma once

#include "../Components/IComponent.h"
#include "../Components/Message.h"

#include <vector>

namespace Ceres
{
    class IEntity
    {
        public:
            IEntity();
            ~IEntity();
            /// Returns true if message is recieved by a component, otherwise returns false.
            virtual bool SendMessage(int message);
        private:
            std::vector<IComponent> _components;

            uint8_t _identifier;

    };
}