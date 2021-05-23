#include "Game.h"
#include "Core/GraphicsDevice.h"

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
        if(!_graphicsDevice->CreateWindow())
        {
            return false;
        }
        return true;
    }

    void Game::Update()
    {

    }

    void Game::Draw()
    {

    }
}