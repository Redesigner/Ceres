#include "ComponentRef.h"

namespace Ceres
{
    ComponentRef::ComponentRef()
        :_listRef(nullptr), _localID(0)
    {}

    ComponentRef::ComponentRef(ComponentList* list, int localID)
        :_listRef(list), _localID(localID)
    {}

    ComponentRef::ComponentRef(const ComponentRef& value)
        :_listRef(value._listRef), _localID(value._localID)
    {}

    ComponentRef::~ComponentRef()
    {}

    IComponent* ComponentRef::operator ->()
    {
        return (*_listRef)[_localID];
    }

    const ComponentRef& ComponentRef::operator=(const ComponentRef& value)
    {
        _listRef = value._listRef;
        _localID = value._localID;
        return *this;
    }
}