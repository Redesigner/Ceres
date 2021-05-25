#pragma once

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
            
        private:
            int _status;
            GraphicsDevice* _graphicsDevice;

    };
}