#pragma once

#include "ComponentList.h"

#include <stdexcept>
#include <fmt/core.h>
#include <type_traits>

namespace Ceres
{
    struct ComponentRefBase
    {
        public:
            ComponentRefBase();
            ComponentRefBase(ComponentList* list, int localID);
            ComponentRefBase(const ComponentRefBase& value);

            ~ComponentRefBase();

            IComponent* operator->() const;

            const ComponentRefBase& operator=(const ComponentRefBase& value);
        protected:
            int _localID;
            ComponentList* _listRef;
    };

    template <typename T>
    struct ComponentRef : public ComponentRefBase
    {
        public:
            ComponentRef()
            {
                static_assert(std::is_base_of<IComponent, T>::value, "The type requested from must be derived from 'IComponent'.");
            }
            ComponentRef(ComponentList* list, int localID)
                : ComponentRefBase(list, localID)
            {
                static_assert(std::is_base_of<IComponent, T>::value, "The type requested from must be derived from 'IComponent'.");
            }

            const ComponentRef operator=(const ComponentRef& value)
            {
                _listRef = value._listRef;
                _localID = value._localID;
                return *this;
            }

            T* operator->() const
            {
                return dynamic_cast<T*>((*_listRef)[_localID]);
            }
            
    };
}