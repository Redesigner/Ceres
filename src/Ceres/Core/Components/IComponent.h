#pragma once

namespace Ceres
{
    class IEntity;

    class IComponent
    {
        public:
            IComponent(const IEntity& parent);
            ~IComponent();
            
            virtual bool recieveMessage();

        private:

        protected:
            const IEntity& parent;
    };
}