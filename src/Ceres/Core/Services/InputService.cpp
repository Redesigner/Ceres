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

    ComponentRef InputService::GenerateComponent(Type type, ComponentPR& params)
    {
        if(type == Type(typeid(ControllerComponent)))
        {
            if(params->Count() == 0)
            {
                _components.Insert(new ControllerComponent(_inputHandler));
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type.name()));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", type.name()));
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