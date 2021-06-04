#include "InputHandler.h"

#include <fmt/core.h>

const int MAX_INPUTMAP_SIZE = 32;
namespace Ceres
{
    InputHandler::InputHandler()
        :_map(std::unordered_map<Button, voidFunctionType>(MAX_INPUTMAP_SIZE))
    {}

    InputHandler::~InputHandler()
    {}

    void InputHandler::BindInput(Button input, voidFunctionType function)
    {
        _map.insert(std::pair<Button, voidFunctionType>(input, function));
    }

    void InputHandler::HandleInput(Button input)
    {
        std::unordered_map<Button, voidFunctionType>::const_iterator get = _map.find(input);
        if(get == _map.end())
        {
            return;
        }
        get->second();
    }
}