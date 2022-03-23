#pragma once

#include "Base/IComponent.h"
#include "../Common/Vector2.h"

#include <string>

namespace Ceres
{
	class TextComponent : public IComponent
	{
		public:
			TextComponent(std::string fontID, float x, float y);
			TextComponent(TextComponent& textComponent);
			TextComponent(TextComponent&& textComponent) noexcept;
			TextComponent();
			~TextComponent();


			const std::string& GetFont() const;

			const std::string& GetContent() const;
			void SetContent(std::string content);

			Vector2 GetPosition() const;
			void SetPosition(Vector2 position);

			bool Updated = false;

		private:
			std::string _content = "";
			/**
			 * @brief An identifier for the font we want to use; the font renderer will take care of finding the font file
			 * 
			 */
			std::string _fontID;
			Vector2 _position;
	};
}