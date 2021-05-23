#include "Game.h"
#include "Core/MainHandler.h"

int main(int, char**)
{
	Ceres::Game* game = new Ceres::Game();
	Ceres::MainHandler* mainHandler = new Ceres::MainHandler(game);
	mainHandler->Loop();

	return 0;
}