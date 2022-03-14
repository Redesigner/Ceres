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

            virtual ComponentPtrBase GenerateComponent(Type type, ComponentPR& params) override;
            virtual TypeList GetAssociatedTypes() const override;

            void Update(double seconds);

        private:
            InputHandler& _inputHandler;
    };
}