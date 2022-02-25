#pragma once

#include <vector>

namespace Ceres
{
    template <typename T>
    struct AssetPtr
    {
        public:
            AssetPtr() {};
            AssetPtr(std::vector<T>& container, int id)	: _container(&container), _id(id) {};
            ~AssetPtr() {};

            T& operator*()
            {
                return _container->at(_id);
            };
            T* operator->()
            {
		        return &_container->at(_id);
	        };

            explicit operator bool() const
            {
                return _container && _container->size() > _id;
            };

        private:
            std::vector<T>* _container = nullptr;
            int _id = 0;
    };
}