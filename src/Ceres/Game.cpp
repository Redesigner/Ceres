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

#include "Core/Components/CameraComponent.h"
#include "Core/Components/ControllerComponent.h"
#include "Core/Components/MovementComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/PhysicsComponent.h"

#include "Core/IO/ContentManager.h"

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
    }

    bool Game::Initialize()
    {
        serviceContainer.AddService<RenderService>(new RenderService(graphicsDevice));
        serviceContainer.AddService<InputService>(new InputService(inputHandler));
        serviceContainer.AddService<PhysicsService>(new PhysicsService(serviceContainer.GetService<RenderService>()));
        serviceContainer.AddService<ActorService>(new ActorService());

        serviceContainer.AddTypeAssociation<CameraComponent, RenderService>();
        serviceContainer.AddTypeAssociation<ControllerComponent, InputService>();
        serviceContainer.AddTypeAssociation<MovementComponent, ActorService>();
        serviceContainer.AddTypeAssociation<RenderComponent, RenderService>();
        serviceContainer.AddTypeAssociation<PhysicsComponent, PhysicsService>();

        inputHandler.BindAxis2D("Movement", Button::Key_up, Button::Key_down, Button::Key_left, Button::Key_right);
        inputHandler.BindAxis("Vertical", Button::Key_q, Button::Key_e);
        inputHandler.BindAxis("Rotation", Button::Key_o, Button::Key_p);
        return true;
    }

    void Game::Load()
    {
        Cube<VertexPositionNormalColor> cube = Cube<VertexPositionNormalColor>(1, 1, 1, Color(181, 206, 245));
        Cube<VertexPositionNormalColor> cubeRed = Cube<VertexPositionNormalColor>(1, 1, 1, Color(216, 25, 30));
        Sphere sphere(1, 20, 32, Color::Blue());
        AssetPtr<Mesh> cubeMesh = graphicsDevice.LoadMesh(cube);
        AssetPtr<Mesh> cubeMeshRed = graphicsDevice.LoadMesh(cubeRed);
        AssetPtr<Effect> texturedEffect = graphicsDevice.LoadEffect("textured");
        AssetPtr<Mesh> roundCubeMesh = graphicsDevice.LoadMesh(ContentManager::LoadMesh("Meshes/RoundCube.obj"), texturedEffect);
        AssetPtr<Texture> testTexture = graphicsDevice.LoadTexture("dummyTex2.png");
        AssetPtr<Texture> cloudTexture = graphicsDevice.LoadTexture("Cloud.png");

        AssetPtr<Mesh> testMesh = graphicsDevice.LoadMesh(ContentManager::LoadMesh("Meshes/test.obj"), texturedEffect);
        
        _world.CreateEntity<Actor>(serviceContainer, testMesh, testTexture);

        IEntity& floor =    _world.CreateEntity<Block>(serviceContainer, 10.0f, 10.0f, 1.0f, cubeMesh);
        IEntity& rail1 =    _world.CreateEntity<Block>(serviceContainer, 10.0f, 0.1f, 0.5f, cubeMeshRed);
        IEntity& rail2 =    _world.CreateEntity<Block>(serviceContainer, 0.1f, 10.0f, 0.5f, cubeMeshRed);
        IEntity& rail3 =    _world.CreateEntity<Block>(serviceContainer, 0.1f, 10.0f, 0.5f, cubeMeshRed);
        IEntity& ramp =     _world.CreateEntity<Block>(serviceContainer, 2.0f, 10.0f, 0.2f, cubeMesh);
        IEntity& plat1 =    _world.CreateEntity<Block>(serviceContainer, 2.0f, 2.0f, 0.5f, roundCubeMesh, cloudTexture);
        IEntity& plat2 =    _world.CreateEntity<Block>(serviceContainer, 2.0f, 2.0f, 0.5f, roundCubeMesh, cloudTexture);
        IEntity& plat3 =    _world.CreateEntity<Block>(serviceContainer, 2.0f, 2.0f, 0.5f, roundCubeMesh, cloudTexture);

        floor.SendMessage("Position", Vector3(0.0f, 0.0f, -2.0f));
        rail1.SendMessage("Position", Vector3(0.0f, 4.95f, -1.25f));
        rail2.SendMessage("Position", Vector3(-4.95f, 0.0f, -1.25f));
        rail3.SendMessage("Position", Vector3(4.95f, 0.0f, -1.25f));
        ramp.SendMessage("Rotate", Vector3(0.0f, 0.0f, 0.5f));
        ramp.SendMessage("Position", Vector3(-2.0f, 7.0f, 0.2f));
        plat1.SendMessage("Position", Vector3(0.0f, 2.0f, 0.0f));
        plat2.SendMessage("Position", Vector3(0.0f, 7.0f, 2.5f));
        plat3.SendMessage("Position", Vector3(0.0f, 12.0f, 5.0f));
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