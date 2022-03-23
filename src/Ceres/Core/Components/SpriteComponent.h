#pragma once

#include "Base/IComponent.h"

#include "../Common/AssetPointer.h"
#include "../Common/Vector2.h"
#include "../Graphics/Texture.h"

namespace Ceres
{
	class SpriteComponent : public IComponent
	{
		public:
			SpriteComponent(AssetPtr<Texture> texture, int x = 0, int y = 0, int w = 0, int h = 0);
			SpriteComponent();
			~SpriteComponent();

			AssetPtr<Texture> Texture;
			Vector2 Position;
			Vector2 Size;
	};
}
