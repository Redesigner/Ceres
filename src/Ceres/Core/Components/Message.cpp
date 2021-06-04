#include "Message.h"

#include <cstdarg>

namespace Ceres
{
    Message::Message(std::string messageType, int argCount,...)
        :Type(messageType)
    {
        _data = std::vector<void*>(argCount);

        va_list args;
        va_start(args, argCount);

        for(int i = 0; i < argCount; i++)
        {
            _data[i] = va_arg(args, void*);
        }

    }

    Message::~Message()
    {}
}