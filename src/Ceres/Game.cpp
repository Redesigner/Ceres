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

        GenericAllocator testAllocator(8192, 1024);
        GenericAllocator::Handle testData1 = testAllocator.allocateBlock(2048);
        GenericAllocator::Handle testData2 = testAllocator.allocateBlock(2048);
        GenericAllocator::Handle testData3 = testAllocator.allocateBlock(2048);
        GenericAllocator::Handle testData4 = testAllocator.allocateBlock(2048);
        GenericAllocator::Handle testData5 = testAllocator.allocateBlock(2048);

        testData4.get()[0] = 'H';
        testData4.get()[1] = 'i';
        testData4.get()[2] = '!';
        testData4.get()[3] = '\0';

        testData3.clear();
        testAllocator.defragmentBlocks(1);
    }

    void Game::Update()
    {
    }

    void Game::Draw()
    {
         _graphicsDevice.Render();
    }
}