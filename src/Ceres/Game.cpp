#include "Game.h"

#include "Core/Common/Vector2.h"
#include "Core/Common/Vector3.h"

#include "Core/Graphics/VertexTypes/VertexPosition.h"
#include "Core/Graphics/VertexTypes/VertexPositionLayout.h"
#include "Core/Graphics/Primitives/Cube.h"

#include "Core/Services/RenderService.h"
#include "Core/Services/InputService.h"
#include "Core/Services/PhysicsService.h"

#include "Core/Entities/Actor.h"
#include "Core/Entities/Block.h"

// test only
#include "Core/Physics/ConvexHull.h"
#include "Core/Physics/Primitives/CubePrimitive.h"
#include "Core/Physics/PhysicsUtilities.h"

#include <fmt/core.h>

void testFunc()
{
    
}

namespace Ceres
{
    Game::Game()
    {
    }

    Game::~Game()
    {
        for(IEntity* entity : _entities)
        {
            delete entity;
        }
    }

    bool Game::Initialize()
    {
        ServiceContainer.AddService<RenderService>(new RenderService(GraphicsDevice));
        ServiceContainer.AddService<InputService>(new InputService(InputHandler));
        ServiceContainer.AddService<PhysicsService>(new PhysicsService());

        InputHandler.BindInput(Button::Key_space, [] {
            fmt::print("Test!\n");
          });
        InputHandler.BindAxis2D("test", Button::Key_up, Button::Key_down, Button::Key_left, Button::Key_right);
        InputHandler.BindAxis("Vertical", Button::Key_q, Button::Key_e);
        InputHandler.BindAxis("Rotation", Button::Key_o, Button::Key_p);

        _entities = std::vector<IEntity*>(4);

        VertexList shape = CubePrimitive(4.0f)._vertices;
        // shape[3] = shape[3] * 4.0f;
        // shape[1] = shape[1] * 4.0f;

        VertexList wrapped = PhysicsUtilities::GiftWrap(shape);
        fmt::print("Gift wrapped: {}\n", wrapped.size());
        for (Vector3 vertex : wrapped)
        {
            fmt::print("Vertex {}\n", vertex.ToString());
        }
        return true;
    }

    void Game::Load()
    {
        Cube cube = Cube(1, 1, 1);
        uint8_t meshId = GraphicsDevice.LoadMesh(cube.Vertices, VertexPositionNormalLayout(), 24, cube.Indices, 36);

        _entities.emplace_back(new Actor(ServiceContainer));
        _entities.emplace_back(new Block(ServiceContainer, 1.0f, 1.0f, 1.0f));
    }

    void Game::Update(double seconds)
    {
        ServiceContainer.GetService<InputService>()->Update(seconds);
        ServiceContainer.GetService<PhysicsService>()->Update(seconds);
    }

    void Game::Draw()
    {
        ServiceContainer.GetService<RenderService>()->RenderComponents();
    }
}