#include "InputService.h"

#include <exception>
#include <fmt/core.h>

namespace Ceres
{
    InputService::InputService(const InputHandler& inputHandler)
        :_inputHandler(inputHandler)
    {}

    InputService::~InputService()
    {}

    ComponentRef InputService::GenerateComponent(std::string typeName, const IEntity& parent, int argCout, void* args)
    {
        if(typeName == "ControllerComponent")
        {

        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", typeName));
        }
    }
}