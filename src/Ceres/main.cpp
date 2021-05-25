#include "Game.h"
#include "Core/Program.h"

int main(int, char**)
{
	Ceres::Game* game = new Ceres::Game();
	Ceres::Program* program = new Ceres::Program(game);
	program->Loop();

	return 0;
}