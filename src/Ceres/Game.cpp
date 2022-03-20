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

#include "Core/IO/ContentManager.h"

#include <fmt/core.h>

void testFunc()
{
    
}

namespace Ceres
{
    Game::Game()
        :graphicsDevice(contentManager)
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

        inputHandler.BindAxis2D("Movement", Button::Key_up, Button::Key_down, Button::Key_left, Button::Key_right);
        inputHandler.BindAxis2D("Movement", 0, 0, -1);

        inputHandler.BindAxis("Vertical", Button::Key_q, Button::Key_e);
        inputHandler.BindAxis("Rotation", Button::Key_o, Button::Key_p);

        inputHandler.BindInput(Button::Key_space, "Jump");
        inputHandler.BindInput(Button::Gamepad_a, "Jump");
        inputHandler.BindInput(Button::Key_pause, "Pause");
        inputHandler.BindInput(Button::Gamepad_start, "Pause");

        return true;
    }

    void Game::Load()
    {
        Cube<VertexPositionNormalColor> cube = Cube<VertexPositionNormalColor>(1, 1, 1, Color(181, 206, 245));
        Cube<VertexPositionNormalColor> cubeRed = Cube<VertexPositionNormalColor>(1, 1, 1, Color(216, 25, 30)); 
        Sphere sphere(1, 20, 32, Color::Blue());
        graphicsDevice.LoadMesh(cube, "cube");
        graphicsDevice.LoadMesh(cubeRed, "cubered");
        graphicsDevice.LoadEffect("textured");
        graphicsDevice.LoadMesh(contentManager.LoadMesh("Meshes/RoundCube.obj"), graphicsDevice.GetEffect("textured"), "roundcube");
        graphicsDevice.LoadTexture("dummyTex2.png", "dummy");
        graphicsDevice.LoadTexture("Cloud.png", "cloud");
        graphicsDevice.LoadTexture("transparency.png", "heart");
        graphicsDevice.LoadMesh(contentManager.LoadMesh("Meshes/test.obj"), graphicsDevice.GetEffect("textured"), "dummy");

        graphicsDevice.LoadFont("arial.ttf");


        _world.CreateEntity<Actor>(serviceContainer);

        IEntity& floor =    _world.CreateEntity<Block>(serviceContainer, 10.0f, 10.0f, 1.0f, "cube");
        IEntity& rail1 =    _world.CreateEntity<Block>(serviceContainer, 10.0f, 0.1f, 0.5f, "cubered");
        IEntity& rail2 =    _world.CreateEntity<Block>(serviceContainer, 0.1f, 10.0f, 0.5f, "cubered");
        IEntity& rail3 =    _world.CreateEntity<Block>(serviceContainer, 0.1f, 10.0f, 0.5f, "cubered");
        IEntity& ramp =     _world.CreateEntity<Block>(serviceContainer, 2.0f, 10.0f, 0.2f, "cube");
        IEntity& plat1 =    _world.CreateEntity<Block>(serviceContainer, 2.0f, 2.0f, 0.5f, "roundcube", "cloud");
        IEntity& plat2 =    _world.CreateEntity<Block>(serviceContainer, 2.0f, 2.0f, 0.5f, "roundcube", "cloud");
        IEntity& plat3 =    _world.CreateEntity<Block>(serviceContainer, 2.0f, 2.0f, 0.5f, "roundcube", "cloud");
        IEntity& block1 =   _world.CreateEntity<Block>(serviceContainer, 1.0f, 1.0f, 1.0f, "cube");

        floor.SendMessage("Position", Vector3(0.0f, 0.0f, -2.0f));
        rail1.SendMessage("Position", Vector3(0.0f, 4.95f, -1.25f));
        rail2.SendMessage("Position", Vector3(-4.95f, 0.0f, -1.25f));
        rail3.SendMessage("Position", Vector3(4.95f, 0.0f, -1.25f));
        ramp.SendMessage("Rotate", Vector3(0.0f, 0.0f, 0.5f));
        ramp.SendMessage("Position", Vector3(-2.0f, 7.0f, 0.2f));
        plat1.SendMessage("Position", Vector3(0.0f, 2.0f, 0.0f));
        plat2.SendMessage("Position", Vector3(0.0f, 7.0f, 2.5f));
        plat3.SendMessage("Position", Vector3(0.0f, 12.0f, 5.0f));
        block1.SendMessage("Position", Vector3(2.0f, 0.0f, 0.0f));
        
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