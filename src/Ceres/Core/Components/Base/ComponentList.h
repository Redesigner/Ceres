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
        private:
            std::vector<IComponent*> _internalList;
            int _size;
            int _capacity;
    };
}