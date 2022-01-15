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
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }

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

            _game->GraphicsDevice.BeginRender();
            _game->Draw();
            _game->GraphicsDevice.EndRender();
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
            case SDL_KEYDOWN:
                {
                    if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    {
                        _exit = true;
                        break;
                    }
                    _game->InputHandler.HandleInput(Buttons::GetButton(event.key.keysym.scancode));
                    break;
                }
            case SDL_CONTROLLERBUTTONDOWN:
                {

                    break;
                }
            case SDL_MOUSEMOTION:
                {
                    _game->InputHandler.HandleCursorInput(event.motion.xrel, event.motion.yrel);
                    break;
                }
            }
        }
    }
}