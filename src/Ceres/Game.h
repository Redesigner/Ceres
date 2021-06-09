#pragma once

#include "Core/Graphics/GraphicsDevice.h"
#include "Core/Components/ComponentRef.h"
#include "Core/Input/InputHandler.h"

#include "Core/Services/RenderService.h"
#include "Core/Services/ServiceContainer.h"

namespace Ceres
{
    class GraphicsDevice;

    class Game
    {
        public:
            Game();
            ~Game();

            bool Initialize();
            void Load();
            void Update(double seconds);
            void Draw();

            InputHandler InputHandler;
            GraphicsDevice GraphicsDevice;
            ServiceContainer ServiceContainer;
            
        private:
            int _status;
            ComponentRef _testComponent;
    };
}