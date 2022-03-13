#include "Program.h"

#include "Game.h"
#include "Input/Buttons.h"

#include <fmt/core.h>

extern "C" 
{
	#include <SDL2/SDL.h>
}

namespace Ceres
{
    Program::Program(Game* game)
    {
        _game = game;
        _exit = !game->Initialize();
        game->Load();
    }

    Program::~Program()
    {}

    void Program::Loop()
    {
        uint64_t last = 0;
        uint64_t ticks = SDL_GetPerformanceCounter();
        uint64_t freq = SDL_GetPerformanceFrequency();
        while(!_exit)
        {
            last = ticks;
            ticks = SDL_GetPerformanceCounter();
            handleEvents();

            _game->Update((double) (ticks - last) / freq);

            _game->graphicsDevice.BeginRender();
            _game->Draw();
            _game->graphicsDevice.EndRender();
        }
    }

    void Program::handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                {
                    _exit = true;
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                {
                    _game->graphicsDevice.LockWindow();
                    break;
                }
            case SDL_KEYDOWN:
                {
                    if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    {
                        _exit = true;
                        break;
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_F11)
                    {
                        _game->graphicsDevice.ToggleFullscreen();
                        break;
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_TAB)
                    {
                        _game->graphicsDevice.UnlockWindow();
                    }
                    _game->inputHandler.HandleInput(Buttons::GetButton(event.key.keysym.scancode));
                    break;
                }
            case SDL_MOUSEMOTION:
                {
                    _game->inputHandler.HandleCursorInput(event.motion.xrel, event.motion.yrel);
                    break;
                }
            case SDL_JOYBUTTONDOWN:
                {
                    _game->inputHandler.HandleInput(Buttons::GetButton(event.jbutton.button));
                    break;
                }
            case SDL_JOYAXISMOTION:
                {

                    break;
                }
            case SDL_JOYDEVICEADDED:
                {
                    _game->inputHandler.RegisterController(event.jdevice.which);
                    break;
                }
            case SDL_WINDOWEVENT:
                {
                    _game->graphicsDevice.ReceiveEvent(event.window);
                    break;
                }
            }
        }
    }
}