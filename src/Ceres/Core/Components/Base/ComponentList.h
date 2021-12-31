#pragma once

#include "IComponent.h"

#include <vector>

namespace Ceres
{
    class ComponentList
    {
        public:
            ComponentList(int size);
            ~ComponentList();

            void Insert(IComponent* component);
            const int Size();

            IComponent* operator[](int);

            typedef IComponent** iterator;
            typedef const IComponent* const_iterator;
            iterator begin() { return &_internalList[0]; }
            const_iterator begin() const { return _internalList[0]; }
            iterator end() { return &_internalList[_size]; }
            const_iterator end() const { return _internalList[_size]; }


        private:
            std::vector<IComponent*> _internalList;
            int _size;
            int _capacity;
    };
}