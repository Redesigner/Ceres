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
            
            /// Get the message's internal data of specified type.
            /// Throws an exception if the requested data type
            /// does not match the internally stored type.
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
            /// Construct a message and pack it with data.
            /// The message must be explicitly destroyed.
            template <typename T>
            static Message Write(std::string name, T data)
            {
                Message message = Message(name);
                message.setData(data);
                return message;
            }

            /// Construct a message without any additional data.
            static Message Write(std::string name)
            {
                return Message(name);
            }

            std::string Type;

        private:
            Message(std::string messageType);

            template <typename T>
            void setData(T&& data)
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