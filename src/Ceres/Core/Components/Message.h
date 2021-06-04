#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Ceres
{
    struct Message
    {
        public:
            Message(std::string messageType, int argCount,...);
            ~Message();

            std::string Type;
        private:
            std::vector<void*> _data;
    };
}