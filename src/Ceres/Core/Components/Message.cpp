#include "Message.h"

namespace Ceres
{
    Message::Message(std::string messageType)
        :Type(messageType)
    {}

    Message::~Message()
    {}
}