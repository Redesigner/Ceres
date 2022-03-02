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
#include "Core/Services/ActorService.h"

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
        serviceContainer.AddService<RenderService>(new RenderService(graphicsDevice));
        serviceContainer.AddService<InputService>(new InputService(inputHandler));
        serviceContainer.AddService<PhysicsService>(new PhysicsService(serviceContainer.GetService<RenderService>()));
        serviceContainer.AddService<ActorService>(new ActorService());

        inputHandler.BindAxis2D("Movement", Button::Key_up, Button::Key_down, Button::Key_left, Button::Key_right);
        inputHandler.BindAxis("Vertical", Button::Key_q, Button::Key_e);
        inputHandler.BindAxis("Rotation", Button::Key_o, Button::Key_p);

        _entities = std::vector<IEntity*>();
        return true;
    }

    void Game::Load()
    {
        Cube<VertexPositionNormalColor> cube = Cube<VertexPositionNormalColor>(1, 1, 1, Color(181, 206, 245));

        Cube<VertexPositionNormalColor> cubeRed = Cube<VertexPositionNormalColor>(1, 1, 1, Color(216, 25, 30));

        Cube<VertexPositionNormalTexture> texturedCube = Cube<VertexPositionNormalTexture>(1, 1, 1);
        Sphere sphere(1, 20, 32, Color::Blue());

        AssetPtr<Mesh> cubeMesh = graphicsDevice.LoadMesh(cube);

        AssetPtr<Mesh> cubeMeshRed = graphicsDevice.LoadMesh(cubeRed);

        AssetPtr<Effect> texturedEffect = graphicsDevice.LoadEffect("textured");
        AssetPtr<Mesh> texturedCubeMesh = graphicsDevice.LoadMesh(texturedCube, texturedEffect);
        AssetPtr<Texture> testTexture = graphicsDevice.LoadTexture("test.png");
        Actor* actor = new Actor(serviceContainer, texturedCubeMesh, testTexture);
        inputHandler.BindInput(Button::Key_pause, [actor](){
            actor->SendMessage(Message::Write<void>("Pause", 0));
        });
        _entities.emplace_back(actor);
 
        Block* floor = new Block(serviceContainer, 10.0f, 10.0f, 1.0f, cubeMesh);
        Block* railing1 = new Block(serviceContainer, 10.0f, 0.1f, 0.5f, cubeMeshRed);
        Block* ramp = new Block(serviceContainer, 2.0f, 10.0f, 0.2f, cubeMesh);
        Block* railing2 = new Block(serviceContainer, 0.1f, 10.0f, 0.5f, cubeMeshRed);

        floor->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.0f, 0.0f, -2.0f)));
        railing1->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.0f, 4.95f, -1.25f)));
        ramp->SendMessage(Message::Write<Vector3>("Rotate", &Vector3(0.0f, 0.0f, 0.5f)));
        ramp->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.0f, 7.0f, 0.2f)));
        railing2->SendMessage(Message::Write<Vector3>("Position", &Vector3(-4.95f, 0.0f, -1.25f)));

        _entities.push_back(std::move(floor));
        _entities.push_back(std::move(railing1));
        _entities.push_back(std::move(ramp));
        _entities.push_back(std::move(railing2));

        // NOTE: because the entity is in the master list, it will be deleted
        // when the game is destroyed, so we don't have to worry about it
        // see the Game destructor...
    }

    void Game::Update(double seconds)
    {
        serviceContainer.GetService<InputService>()->Update(seconds);
        serviceContainer.GetService<PhysicsService>()->Update(seconds);
    }

    void Game::Draw()
    {
        graphicsDevice.Render();
    }
}