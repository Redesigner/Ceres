#pragma once

#include "IService.h"
#include "../Input/InputHandler.h"
#include "../Components/Base/ComponentList.h"

namespace Ceres
{
    class InputService : public IService
    {
        public:
            InputService(InputHandler& inputHandler);
            ~InputService();

            virtual ComponentRefBase GenerateComponent(Type type, ComponentPR& params) override;
            void Update(double seconds);

        private:
            InputHandler& _inputHandler;
    };
}