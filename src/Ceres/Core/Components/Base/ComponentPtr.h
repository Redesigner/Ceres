#pragma once

#include "ComponentList.h"

#include <stdexcept>
#include <fmt/core.h>
#include <type_traits>

namespace Ceres
{
    struct ComponentPtrBase
    {
        public:
            ComponentPtrBase();
            ComponentPtrBase(ComponentList* list, int localID);
            ComponentPtrBase(const ComponentPtrBase& value);

            ~ComponentPtrBase();

            IComponent* operator->() const;

            const ComponentPtrBase& operator=(const ComponentPtrBase& value);
        protected:
            int _localID;
            ComponentList* _listRef;
    };

    template <typename T>
    struct ComponentRef : public ComponentPtrBase
    {
        public:
            ComponentRef()
            {
                static_assert(std::is_base_of<IComponent, T>::value, "The type requested from must be derived from 'IComponent'.");
            }
            ComponentRef(ComponentList* list, int localID)
                : ComponentPtrBase(list, localID)
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