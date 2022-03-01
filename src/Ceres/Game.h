#pragma once

#include <vector>

#include "Core/Graphics/GraphicsDevice.h"
#include "Core/Input/InputHandler.h"
#include "Core/Services/RenderService.h"
#include "Core/Services/ServiceContainer.h"

#include "Core/Entities/Base/IEntity.h"

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

            InputHandler inputHandler;
            GraphicsDevice graphicsDevice;
            ServiceContainer serviceContainer;
            
        private:
            int _status;
            std::vector<IEntity*> _entities;
    };
}