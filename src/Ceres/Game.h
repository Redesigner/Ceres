#pragma once

#include "Core/Graphics/VertexCollection.h"
#include "Core/Graphics/VertexTypes/IVertexType.h"
#include "Core/Graphics/VertexTypes/VertexPosition.h"

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
            VertexCollection<VertexPosition>* _testCollection;
    };
}