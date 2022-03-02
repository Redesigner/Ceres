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

        Cube<VertexPositionNormalColor> cubeRed = Cube<VertexPositionNormalColor>(1, 1, 1, Color(255, 0, 0));
        Cube<VertexPositionNormalColor> cubeGreen = Cube<VertexPositionNormalColor>(1, 1, 1, Color(0, 255, 0));
        Cube<VertexPositionNormalColor> cubeBlue = Cube<VertexPositionNormalColor>(1, 1, 1, Color(0, 0, 255));

        Cube<VertexPositionNormalTexture> texturedCube = Cube<VertexPositionNormalTexture>(1, 1, 1);
        Sphere sphere(1, 20, 32, Color::Blue());

        AssetPtr<Mesh> cubeMesh = graphicsDevice.LoadMesh(cube);

        AssetPtr<Mesh> cubeMeshRed = graphicsDevice.LoadMesh(cubeRed);
        AssetPtr<Mesh> cubeMeshGreen = graphicsDevice.LoadMesh(cubeGreen);
        AssetPtr<Mesh> cubeMeshBlue = graphicsDevice.LoadMesh(cubeBlue);

        AssetPtr<Effect> texturedEffect = graphicsDevice.LoadEffect("textured");
        AssetPtr<Mesh> texturedCubeMesh = graphicsDevice.LoadMesh(texturedCube, texturedEffect);
        AssetPtr<Texture> testTexture = graphicsDevice.LoadTexture("test.png");
        Actor* actor = new Actor(serviceContainer, texturedCubeMesh, testTexture);
        inputHandler.BindInput(Button::Key_pause, [actor](){
            actor->SendMessage(Message::Write<void>("Pause", 0));
        });
        _entities.emplace_back(actor);
 
        Block* b1 = new Block(serviceContainer, 2.0f, 5.0f, 1.0f, cubeMesh);
        Block* b2 = new Block(serviceContainer, 5.0f, 1.0f, 1.0f, cubeMesh);
        Block* b3 = new Block(serviceContainer, 10.0f, 2.0f, 1.0f, cubeMesh);
        Block* b4 = new Block(serviceContainer, 0.1f, 5.0f, 0.5f, cubeMesh);

        Block* bX = new Block(serviceContainer, 1.0f, 0.1f, 0.1f, cubeMeshRed);
        Block* bY = new Block(serviceContainer, 0.1f, 1.0f, 0.1f, cubeMeshGreen);
        Block* bZ = new Block(serviceContainer, 0.1f, 0.1f, 1.0f, cubeMeshBlue);


        b1->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.0f, 0.0f, -2.0f)));
        b2->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.0f, -3.0f, -2.0f)));
        b3->SendMessage(Message::Write<Vector3>("Rotate",   &Vector3(0.0f, -0.5f, 0.0f)));
        b3->SendMessage(Message::Write<Vector3>("Position", &Vector3(3.0f, 0.0f, -0.7f)));
        b4->SendMessage(Message::Write<Vector3>("Position", &Vector3(-1.0f, 0.0f, -1.25f)));

        bX->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.5f, 0.0f, 3.0f)));
        bY->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.0f, 0.5f, 3.0f)));
        bZ->SendMessage(Message::Write<Vector3>("Position", &Vector3(0.0f, 0.0f, 3.5f)));

        _entities.push_back(std::move(b1));
        _entities.push_back(std::move(b2));
        _entities.push_back(std::move(b3));
        _entities.push_back(std::move(b4));

        _entities.push_back(std::move(bX));
        _entities.push_back(std::move(bY));
        _entities.push_back(std::move(bZ));
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