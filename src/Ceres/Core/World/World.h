#pragma once

#include "../Entities/Base/IEntity.h"

namespace Ceres
{
	/**
	 * @brief Object containing all of the entities currently in the game.
	 * 
	 */
	class World
	{
		public:
			World();
			~World();

			template <typename T, typename... Ts>
			IEntity& CreateEntity(Ts&&... args)
			{
				T component = T(args...);
				_entities.push_back(std::move(component));
				return _entities.at(_entities.size() - 1);
			}

		private:
			std::vector<IEntity> _entities;
	};
}