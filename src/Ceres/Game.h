#pragma once

#include "Core/Graphics/GraphicsDevice.h"
#include "Core/Input/InputHandler.h"

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
            void Update();
            void Draw();

            InputHandler InputHandler;
            
        private:
            int _status;
            GraphicsDevice _graphicsDevice;
    };
}