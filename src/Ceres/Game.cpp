#include "Game.h"

#include "Core/Common/Vector3.h"
#include "Core/Graphics/GraphicsDevice.h"
#include "Core/Graphics/VertexCollection.h"

namespace Ceres
{
    Game::Game()
    {
        _status = 0;
        _graphicsDevice = new GraphicsDevice();
    }

    Game::~Game()
    {
        delete _graphicsDevice;
    }

    bool Game::Initialize()
    {
        return true;
    }

    void Game::Load()
    {
        Vector3 verts[] = {Vector3(-1, -1, -1), Vector3(-1, 1, -1), Vector3(1, 1, -1), Vector3(1, -1, -2)};
        unsigned int indices[] = {0, 1, 2, 0, 2, 3};
        _graphicsDevice->LoadCollection(new VertexCollection(verts, 4, indices, 6));
    }

    void Game::Update()
    {

    }

    void Game::Draw()
    {
        _graphicsDevice->Render();
    }
}