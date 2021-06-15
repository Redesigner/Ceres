#include "InputService.h"

#include "../Components/ControllerComponent.h"

#include <exception>
#include <fmt/core.h>

namespace Ceres
{
    InputService::InputService(const InputHandler& inputHandler)
        :_inputHandler(inputHandler)
    {}

    InputService::~InputService()
    {}

    ComponentRef InputService::GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args)
    {
        if(typeName == "ControllerComponent")
        {
            if(argCount == 0)
            {
                _components.Insert(new ControllerComponent(parent, _inputHandler));
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", typeName));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", typeName));
        }
    }

    void InputService::Update(double seconds)
    {
        for(int i = 0; i < _components.Size(); i++)
        {
            ((ControllerComponent*) _components[i])->Update(seconds);
        }
    }
}