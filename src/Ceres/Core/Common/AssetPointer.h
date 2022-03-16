#pragma once

#include <vector>

namespace Ceres
{
    /**
     * @brief A weak reference to an asset that is managed by some other class. Can be zero-initialized
     * 
     * @tparam AssetType
     */
    template <typename AssetType>
    struct AssetPtr
    {
        public:
            AssetPtr(std::vector<AssetType>& container, int id)	: _container(&container), _id(id) {};
            AssetPtr() {};
            ~AssetPtr() {};

            AssetType& operator*()
            {
                return _container->at(_id);
            };
            AssetType* operator->()
            {
		        return &_container->at(_id);
	        };
            const AssetType* operator->() const
            {
                return &_container->at(_id);
            }

            /**
             * @brief Does the asset exist?
             * 
             * @return true if there is an asset in the associated container
             * @return false otherwise
             */
            explicit operator bool() const
            {
                return _container && _container->size() > _id;
            };

        private:
            std::vector<AssetType>* _container = nullptr;
            int _id = 0;
    };
}