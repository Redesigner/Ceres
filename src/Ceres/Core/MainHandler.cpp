#include "MainHandler.h"

#include "Game.h"

extern "C" 
{
	#include <SDL2/SDL.h>
}

namespace Ceres
{
    MainHandler::MainHandler(Game* game)
    {
        _game = game;
        _exit = !game->Initialize();
    }

    void MainHandler::Loop()
    {
        while(!_exit)
        {
            handleEvents();

            _game->Update();
            _game->Draw();
        }
    }

    void MainHandler::handleEvents()
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