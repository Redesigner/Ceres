#include "Game.h"

#include "Core/Common/Vector2.h"
#include "Core/Common/Vector3.h"

#include "Core/Graphics/VertexTypes/VertexPosition.h"
#include "Core/Graphics/VertexTypes/VertexPositionLayout.h"
#include "Core/Graphics/Primitives/Cube.h"

#include "Core/Services/RenderService.h"
#include "Core/Services/InputService.h"

#include <fmt/core.h>

void testFunc()
{
    fmt::print("Test!\n");
}

namespace Ceres
{
    Game::Game()
    {
    }

    Game::~Game()
    {
        delete _testActor;
    }

    bool Game::Initialize()
    {
        ServiceContainer.AddService<RenderService>(new RenderService(GraphicsDevice));
        ServiceContainer.AddService<InputService>(new InputService(InputHandler));

        InputHandler.BindInput(Button::Key_space, &testFunc);
        InputHandler.BindAxis("test", Button::Key_up, Button::Key_down, Button::Key_left, Button::Key_right);

        return true;
    }

    void Game::Load()
    {
        Cube cube = Cube(1, 1, 1);
        uint8_t meshId = GraphicsDevice.LoadMesh(cube.Vertices, VertexPositionNormalLayout(), 24, cube.Indices, 36);
        _testActor = new Actor(ServiceContainer);
    }

    void Game::Update(double seconds)
    {
        ServiceContainer.GetService<InputService>()->Update(seconds);
    }

    void Game::Draw()
    {
        ServiceContainer.GetService<RenderService>()->RenderComponents();
    }
}