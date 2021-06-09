#pragma once

#include "Message.h"

namespace Ceres
{
    class IEntity;

    class IComponent
    {
        public:
            IComponent(const IEntity& parent);
            ~IComponent();
            
            virtual bool RecieveMessage(Message* message) = 0;

        private:

        protected:
            const IEntity& parent;
    };
}