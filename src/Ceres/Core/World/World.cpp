#include "World.h"

namespace Ceres
{
	World::World()
	{
		_entities = std::vector<IEntity>();
		_entities.reserve(10);
	}

	World::~World()
	{
	}
}