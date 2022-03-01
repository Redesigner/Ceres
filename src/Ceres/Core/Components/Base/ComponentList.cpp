#include "ComponentList.h"

namespace Ceres
{
    using iterator = IComponent**;
    using const_iterator = const IComponent**;

    ComponentList::ComponentList()
    :_internalList(std::vector<IComponent*>())
    {}

    ComponentList::ComponentList(int size)
        :_internalList(std::vector<IComponent*>())
    {
        _internalList.reserve(size);
    }

    ComponentList::~ComponentList()
    {
        for(IComponent* component : _internalList)
        {
            delete component;
        }
    }

    IComponent* ComponentList::operator[](int i)
    {
        return _internalList[i];
    }

    void ComponentList::Insert(IComponent* component)
    {
        _internalList.push_back(component);
    }

    const int ComponentList::Size() const
    {
        return _internalList.size();
    }

    iterator ComponentList::begin()
    {
        if (_internalList.size() == 0)
        {
            return nullptr;
        }
        return _internalList.data();
    }

    /* const_iterator ComponentList::begin() const
    {
        if (_internalList.size() == 0)
        {
            return nullptr;
        }
        return _internalList.data();
    } */

    iterator ComponentList::end()
    {
        if (_internalList.size() == 0)
        {
            return nullptr;
        }
        return _internalList.data() + Size();
    }

    /* const iterator ComponentList::end() const
    {
        if (_internalList.size() == 0)
        {
            return nullptr;
        }
        return _internalList.data() + Size();
    } */
}