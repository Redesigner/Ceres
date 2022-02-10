#include "Game.h"

#include "Core/Common/Vector2.h"
#include "Core/Common/Vector3.h"
#include "Core/Common/VertexList.h"

#include "Core/Graphics/VertexTypes/VertexPosition.h"
#include "Core/Graphics/VertexTypes/VertexPositionLayout.h"
#include "Core/Graphics/Primitives/Cube.h"
#include "Core/Graphics/Primitives/Sphere.h"

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
        ServiceContainer.AddService<PhysicsService>(new PhysicsService(ServiceContainer.GetService<RenderService>()));

        InputHandler.BindInput(Button::Key_space, [] {
            fmt::print("Test!\n");
          });
        InputHandler.BindAxis2D("test", Button::Key_up, Button::Key_down, Button::Key_left, Button::Key_right);
        InputHandler.BindAxis("Vertical", Button::Key_q, Button::Key_e);
        InputHandler.BindAxis("Rotation", Button::Key_o, Button::Key_p);

        _entities = std::vector<IEntity*>(4);
        return true;
    }

    void Game::Load()
    {
        Cube cube = Cube(1, 1, 1);
        GraphicsDevice.LoadMesh(cube.Vertices, VertexPositionNormalLayout(), 24, cube.Indices, 36);

        Sphere sphere = Sphere(.25f, 16, 16);
        GraphicsDevice.LoadMesh(sphere.Vertices, VertexPositionNormalLayout(), sphere.VertexCount, sphere.Indices, sphere.IndexCount);


        _entities.emplace_back(new Actor(ServiceContainer));

        Block* b1 = new Block(ServiceContainer, 1.0f, 5.0f, 1.0f);
        Block* b2 = new Block(ServiceContainer, 5.0f, 1.0f, 1.0f);
        b1->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.0f, 0.0f, -2.0f)));
        b2->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.0f, -3.0f, -2.0f)));

        _entities.emplace_back(b1);
        _entities.emplace_back(b2); 
        // NOTE: because the entity is in the master list, it will be deleted when the game is destroyed, so we don't have to worry about it
        // see the Game destructor...
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