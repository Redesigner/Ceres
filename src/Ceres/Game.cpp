#include "Game.h"

#include "Core/Common/Vector3.h"
#include "Core/Graphics/GraphicsDevice.h"
#include "Core/Graphics/VertexTypes/VertexPosition.h"
#include "Core/Graphics/VertexTypes/VertexPositionLayout.h"

#include "Core/Memory/GenericAllocator.h"

namespace Ceres
{
    Game::Game()
    {
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
        VertexPosition verts[] = {
            Vector3(-1, -1, 1), Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1),
            Vector3(-1, -1, -1), Vector3(-1, 1, -1), Vector3(1, 1, -1), Vector3(1, -1, -1)};
        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
            4, 5, 6, 4, 6, 7,
            1, 2, 5, 2, 5, 6,
            0, 3, 4, 3, 4, 7,
            0, 1, 4, 1, 4, 5,
            2, 3, 6, 3, 6, 7
        };

        _graphicsDevice.LoadMesh(verts, VertexPositionLayout(), 8, indices, 36);
        GenericAllocator allocator(4096, 32);
        GenericAllocator::WeakHandle weakData1;
        {
            GenericAllocator::Handle data1 = allocator.allocate(256);
            data1.getData()[0] = 'Q';
            weakData1 = data1;
        }
        weakData1.pin().getData();
    }

    void Game::Update()
    {
    }

    void Game::Draw()
    {
         _graphicsDevice.Render();
    }
}