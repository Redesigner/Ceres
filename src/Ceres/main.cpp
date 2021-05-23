#include "Game.h"
extern "C" 
{
	#include <SDL2/SDL.h>
}

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int, char**)
{
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
	}
	else
	{
		window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window != nullptr)
		{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(1000);
		}
	}
	Game game;
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}