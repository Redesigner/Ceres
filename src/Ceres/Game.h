#pragma once

#include <vector>

#include "Core/Graphics/GraphicsDevice.h"
#include "Core/Input/InputHandler.h"
#include "Core/Services/RenderService.h"
#include "Core/Services/ServiceContainer.h"
#include "Core/World/World.h"

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

            // Public members with the same name as the class types should be lowercase
            InputHandler inputHandler;
            ContentManager contentManager;
            GraphicsDevice graphicsDevice;
            ServiceContainer serviceContainer;
            
        private:
            int _status;
            World _world;
    };
}