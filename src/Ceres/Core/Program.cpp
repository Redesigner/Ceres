#include "Program.h"

#include "Game.h"

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

    void Program::Loop()
    {
        while(!_exit)
        {
            handleEvents();

            _game->Update();
            _game->Draw();
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
            }
        }
    }
}