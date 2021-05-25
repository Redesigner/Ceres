#include "Game.h"

#include "Core/Vector3.h"
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

    void Game::Load()
    {
        std::vector<Vector3> vertices = {Vector3(-0.5f, -0.5f, 0), Vector3(0, 0.5f, 0), Vector3(0.5f, -0.5f, 0)};
        _graphicsDevice->LoadVertices(vertices);
    }

    void Game::Update()
    {

    }

    void Game::Draw()
    {
        _graphicsDevice->Render();
    }
}