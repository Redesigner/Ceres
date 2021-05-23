#pragma once

namespace Ceres
{
    class GraphicsDevice;

    class Game
    {
        public:
            Game();
            ~Game();

            bool Game::Initialize();
            void Game::Update();
            void Game::Draw();
            
        private:
            int _status;
            GraphicsDevice* _graphicsDevice;

    };
}