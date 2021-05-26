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
        Vector3 verts[] = {
            Vector3(-1, -1, 1), Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1),
            Vector3(-1, -1, -1), Vector3(-1, 1, -1), Vector3(1, 1, -1), Vector3(1, -1, -1)};
        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
            4, 5, 6, 4, 6, 7,
            1, 2, 5, 2, 5, 6
        };
        _testCollection = new VertexCollection(verts, 8, indices, 18);
        _graphicsDevice->LoadCollection(_testCollection);
    }

    void Game::Update()
    {
        _testCollection->ApplyTransform(Matrix::RotationAlongY(0.0001f));
    }

    void Game::Draw()
    {
        _graphicsDevice->Render();
    }
}