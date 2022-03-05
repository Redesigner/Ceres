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
            Message(Message& message);
            
            template <typename T>
            T GetData()
            {
                std::type_index requestedType = std::type_index(typeid(T));
                if(requestedType == _dataType)
                {
                    return *reinterpret_cast<T*>(_data);
                }
                throw std::invalid_argument("That data type is not stored inside the message.");
            }
            template <typename T>
            static Message Write(std::string name, T data)
            {
                Message message = Message(name);
                message.SetData(data);
                return message;
            }

            static Message Write(std::string name)
            {
                return Message(name);
            }

            std::string Type;

        private:
            Message(std::string messageType);

            template <typename T>
            void SetData(T&& data)
            {
                if (_data == nullptr)
                {
                    _dataType = std::type_index(typeid(T));
                    _dataSize = sizeof(T);
                    _data = new char[_dataSize];
                    memcpy(_data, &data, _dataSize);
                }
            }

            char* _data = nullptr;
            std::size_t _dataSize = 0;
            std::type_index _dataType = (typeid(char));
    };
}