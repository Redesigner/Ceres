#include "Game.h"
#include "Core/Program.h"

int main(int, char**)
{
	Ceres::Game game;
	Ceres::Program program(&game);
	program.Loop();

	return 0;
}