#include "TextComponent.h"

namespace Ceres
{
	TextComponent::TextComponent(std::string fontID, float x, float y)
		:IComponent(std::type_index(typeid(TextComponent)))
	{
		_fontID = fontID;
		_position.X = x;
		_position.Y = y;
		_content = std::string();

		addMessageHandler("Text", [](IComponent* component, Message& message)
			{
				TextComponent* text = static_cast<TextComponent*>(component);
				std::string& data = message.GetData<std::string>();
				if (data[0] < 0)
				{
					data = "error encountered";
				}
				text->SetContent(data);
			});
	}

	TextComponent::TextComponent(TextComponent& textComponent)
		:IComponent(std::type_index(typeid(TextComponent)))
	{
		_fontID = textComponent._fontID;
		_content = std::string(textComponent._content);
	}

	TextComponent::TextComponent(TextComponent&& textComponent) noexcept
		:IComponent(std::type_index(typeid(TextComponent)))
	{
		_fontID = textComponent._fontID;
		_content = std::string(textComponent._content);
	}

	TextComponent::TextComponent()
		:IComponent(std::type_index(typeid(TextComponent)))
	{

	}

	TextComponent::~TextComponent()
	{

	}

	const std::string& TextComponent::GetFont() const
	{
		return _fontID;
	}

	const std::string& TextComponent::GetContent() const
	{
		return _content;
	}

	void TextComponent::SetContent(std::string content)
	{
		if (content != _content)
		{
			Updated = true;
			_content = content;
		}
	}

	Vector2 TextComponent::GetPosition() const
	{
		return _position;
	}

	void TextComponent::SetPosition(Vector2 position)
	{
		if (position != _position)
		{
			Updated = true;
			_position = position;
		}
	}
}