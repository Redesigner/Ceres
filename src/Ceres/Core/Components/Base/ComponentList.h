#pragma once

#include "IComponent.h"

#include <vector>

namespace Ceres
{
    class ComponentList
    {
        using iterator = IComponent**;
        using const_iterator = const IComponent**;

        public:
            ComponentList();
            ComponentList(int size);
            ~ComponentList();

            void Insert(IComponent* component);
            const int Size() const;

            IComponent* operator[](int);

            iterator begin();
            // const_iterator begin() const;
            iterator end();
            // const_iterator end() const;


        private:
            std::vector<IComponent*> _internalList;
        };
}