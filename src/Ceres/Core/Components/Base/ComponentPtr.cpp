#include "ComponentPtr.h"

namespace Ceres
{
    ComponentPtrBase::ComponentPtrBase()
        :_listRef(nullptr), _localID(0)
    {}

    ComponentPtrBase::ComponentPtrBase(ComponentList* list, int localID)
        :_listRef(list), _localID(localID)
    {}

    ComponentPtrBase::ComponentPtrBase(const ComponentPtrBase& value)
        :_listRef(value._listRef), _localID(value._localID)
    {}

    ComponentPtrBase::~ComponentPtrBase()
    {}

    IComponent* ComponentPtrBase::operator->() const
    {
        return (*_listRef)[_localID];
    }

    const ComponentPtrBase& ComponentPtrBase::operator=(const ComponentPtrBase& value)
    {
        _listRef = value._listRef;
        _localID = value._localID;
        return *this;
    }
}