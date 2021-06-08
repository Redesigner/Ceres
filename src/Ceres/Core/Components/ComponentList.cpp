#include "ComponentList.h"

namespace Ceres
{
    ComponentList::ComponentList(int size)
        :_internalList(std::vector<IComponent*>(size)), _size(0), _capacity(size)
    {}

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
        _internalList[_size++] = (component);
    }

    const int ComponentList::Size()
    {
        return _size;
    }
}