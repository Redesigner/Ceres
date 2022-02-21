#include "InputService.h"

#include "../Components/ControllerComponent.h"

#include <exception>
#include <fmt/core.h>

namespace Ceres
{
    InputService::InputService(InputHandler& inputHandler)
        :_inputHandler(inputHandler)
    {}

    InputService::~InputService()
    {}

    ComponentRef InputService::GenerateComponent(std::string type, const IEntity& parent, ComponentParams* params)
    {
        if(type == "ControllerComponent")
        {
            if(params->Count() == 0)
            {
                _components.Insert(new ControllerComponent(parent, _inputHandler));
                delete params;
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", type));
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