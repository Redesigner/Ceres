#pragma once

#include "ComponentList.h"

namespace Ceres
{
    struct ComponentRef
    {
        public:
            ComponentRef();
            ComponentRef(ComponentList* list, int localID);
            ComponentRef(const ComponentRef& value);

            ~ComponentRef();

            const IComponent* operator->();
            const ComponentRef& operator =(const ComponentRef& value);
        private:
            int _localID;
            ComponentList* _listRef;
    };
}