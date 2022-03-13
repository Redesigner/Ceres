#include "SpriteComponent.h"

namespace Ceres
{
	SpriteComponent::SpriteComponent(AssetPtr<Ceres::Texture> texture, int x, int y, int w, int h)
		:IComponent(std::type_index(typeid(SpriteComponent)))
	{
		Texture = texture;
		Position = Vector2(x, y);
		Size = Vector2(w, h);
	}

	SpriteComponent::SpriteComponent()
		:SpriteComponent(AssetPtr<Ceres::Texture>())
	{}

	SpriteComponent::~SpriteComponent()
	{}

	bool SpriteComponent::ReceiveMessage(Message& message)
	{
		return false;
	}
}