#include "Message.h"

namespace Ceres
{
    Message::Message(std::string messageType)
        :Type(messageType)
    {}

	Message::Message(Message& message)
		:Type(message.Type)
	{
		_dataSize = message._dataSize;
		_data = new char[_dataSize];
		_dataType = message._dataType;
		memcpy(_data, message._data, _dataSize);
	}

    Message::~Message()
    {
		if (_data != nullptr)
		{
        	delete[] _data;
			_data = nullptr;
		}
    }
}