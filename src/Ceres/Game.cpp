#include "Game.h"
#include "Core/Graphics/GraphicsDevice.h"

namespace Ceres
{
    Game::Game()
    {
        _status = 0;
        _graphicsDevice = new GraphicsDevice();
    }

    Game::~Game()
    {
    }

    bool Game::Initialize()
    {
        return true;
    }

    void Game::Update()
    {

    }

    void Game::Draw()
    {

    }
}