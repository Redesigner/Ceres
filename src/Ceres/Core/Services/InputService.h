#pragma once

#include "IService.h"
#include "../Input/InputHandler.h"
#include "../Components/Base/ComponentList.h"

namespace Ceres
{
    class InputService : IService
    {
        public:
            InputService(const InputHandler& inputHandler);
            ~InputService();

            virtual ComponentRef GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args) override;
        
        private:
            const InputHandler& _inputHandler;
    };
}