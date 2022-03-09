#include "ComponentRef.h"

namespace Ceres
{
    ComponentRefBase::ComponentRefBase()
        :_listRef(nullptr), _localID(0)
    {}

    ComponentRefBase::ComponentRefBase(ComponentList* list, int localID)
        :_listRef(list), _localID(localID)
    {}

    ComponentRefBase::ComponentRefBase(const ComponentRefBase& value)
        :_listRef(value._listRef), _localID(value._localID)
    {}

    ComponentRefBase::~ComponentRefBase()
    {}

    IComponent* ComponentRefBase::operator->() const
    {
        return (*_listRef)[_localID];
    }

    const ComponentRefBase& ComponentRefBase::operator=(const ComponentRefBase& value)
    {
        _listRef = value._listRef;
        _localID = value._localID;
        return *this;
    }
}