#pragma once

#include <memory>
#include <string>

namespace Ceres
{
    struct Message
    {
        public:
            Message(std::string messageType, void* data);
            ~Message();

            std::string Type;
            template <typename T>
            T* GetData()
            {
                return (T*)(_data);
            }
        private:
            void* _data;
    };
}