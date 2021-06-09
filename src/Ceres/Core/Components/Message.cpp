#include "Message.h"

namespace Ceres
{
    Message::Message(std::string messageType, void* data)
        :Type(messageType), _data(data)
    {}

    Message::~Message()
    {}
}