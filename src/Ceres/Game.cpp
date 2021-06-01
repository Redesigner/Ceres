#include "Game.h"

#include "Core/Common/Vector3.h"
#include "Core/Graphics/GraphicsDevice.h"
#include "Core/Graphics/VertexTypes/VertexPosition.h"
#include "Core/Graphics/VertexTypes/VertexPositionLayout.h"

#include "Core/Memory/FirstFreeAllocator.h"

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

        FirstFreeAllocator allocator(8192, 64);

        uint8* data1 = allocator.allocateBlock(4096);
        uint8* data2 = allocator.allocateBlock(2048);
        uint8* data3 = allocator.allocateBlock(8192);
        uint8* data4 = allocator.allocateBlock(2048);
        
        allocator.freeBlock(data2, 2048);
        allocator.freeBlock(data4, 2048);

        uint8* data5 = allocator.allocateBlock(4096);

        allocator.freeBlock(data1, 4096);
        allocator.freeBlock(data5, 4096);
        if (data3)
        {
            allocator.freeBlock(data3, 8192);
        }
    }

    void Game::Update()
    {
    }

    void Game::Draw()
    {
         _graphicsDevice.Render();
    }
}