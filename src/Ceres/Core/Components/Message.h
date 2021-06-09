#pragma once

#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <string>

namespace Ceres
{
    struct Message
    {
        public:
            ~Message();
            
            template <typename T>
            T GetData()
            {
                if(std::type_index(typeid(T)) == _type)
                {
                    return *(T*)(_data);
                }
                throw std::invalid_argument("That data type is not stored inside the message.");
            }
            template <typename T>
            static Message* Write(std::string name, T* data)
            {
                Message* message = new Message(name);
                message->SetData<T>(data);
                return message;
            }

            std::string Type;

        private:
            Message(std::string messageType);

            template <typename T>
            void SetData(T* data)
            {
                _type = std::type_index(typeid(T));
                _data = data;
            }

            void* _data;
            std::type_index _type = (typeid(char));
    };
}