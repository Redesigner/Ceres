extern "C"
{
	#include <SDL2/SDL.h>
}

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int, char**)
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
	}
	else
	{
		window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window != NULL)
		{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(1000);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}