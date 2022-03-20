#include "FontBatcher.h"

#include "VertexTypes/VertexPositionTextureLayout.h"

#include <exception>

namespace Ceres
{
	FontBatcher::FontBatcher(unsigned int size, AssetPtr<FontAtlas> fontAtlas, AssetPtr<Effect> spriteEffect)
		:_iBO(size * 6), _vAO(VertexPositionTextureLayout::Get()), _vBO(size * 4, VertexPositionTextureLayout::Get())
	{
		_vAO.SetAttributes();
		_fontAtlas = fontAtlas;
		_spriteEffect = spriteEffect;
	}

	FontBatcher::FontBatcher(FontBatcher&& fontBatcher)
	    :_vAO(std::move(fontBatcher._vAO)), _vBO(std::move(fontBatcher._vBO)), _iBO(std::move(fontBatcher._iBO)), _spriteEffect(fontBatcher._spriteEffect)
	{
		_spriteEffect = fontBatcher._spriteEffect;
		_fontAtlas = fontBatcher._fontAtlas;
	}

	FontBatcher::~FontBatcher()
	{}

	/**
	 * @brief Attach our buffers and textures to the current OpenGL state
	 * 
	 */
	void FontBatcher::Bind()
	{
		_vAO.Bind();
		_iBO.Bind();
		_spriteEffect->Begin();
		_spriteEffect->SetTexture("tex", _fontAtlas->GetTextureID());
        _spriteEffect->SetMatrix2D("transform", _screenSpace);
	}

	void FontBatcher::SetScreenSize(unsigned int x, unsigned int y)
	{
		_screenSpace = Matrix2D::Sprite(0, 0, 1, -1, x, y);
	}

	/**
	 * @brief Populate the local buffers with the necessary data for rendering text
	 * 
	 * @param string Text to be displayed
	 * @param xPos
	 * @param yPos 
	 */
	void FontBatcher::LoadString(std::string string, int xPos, int yPos)
	{
		int currentX = xPos;
		int currentY = yPos;
		for (int i = 0; i < string.length(); i++)
		{
			if (string[i] == '\\n' || string[i] == 10)
			{
				currentX = xPos;
				currentY += _fontAtlas->GetLineHeight();
				continue;
			}
			generateGlyphPrimitive(string[i], currentX, currentY);
			currentX += _fontAtlas->GetCharUV(string[i]).Advance;
			if (i + 1 < string.length())
			{
				currentX += _fontAtlas->GetKerning(string[i], string[i + 1]);
			} 
		}

		_unbufferedChars += string.size(); 
	}

	/**
	 * @brief Get the total number of vertices to render
	 * 
	 * @return unsigned int 
	 */
	unsigned int FontBatcher::GetVertexCount() const
	{
		return _bufferedChars * 6;
	}

	void FontBatcher::RegisterComponent(ComponentPtr<TextComponent> component)
	{
		_componentsToBatch.push_back(component);
		Vector2 position = component->GetPosition();
		LoadString(component->GetContent(), position.X, position.Y);
	}

	void FontBatcher::UnregisterComponent(ComponentPtr<TextComponent> component)
	{
		for (auto i = _componentsToBatch.begin(); i < _componentsToBatch.end(); i++)
		{
			if (component == *i)
			{
				_componentsToBatch.erase(i);
			}
		}
	}

	void FontBatcher::Regenerate()
	{
		_glyphVertices.clear();
		_glyphIndices.clear();
		for (ComponentPtr<TextComponent> component : _componentsToBatch)
		{
			Vector2 position = component->GetPosition();
			LoadString(component->GetContent(), position.X, position.Y);
			component->Updated = false;
		}
		BufferData();
	}

	bool FontBatcher::CheckForUpdates() const
	{
		for (ComponentPtr<TextComponent> component : _componentsToBatch)
		{
			if (component->Updated)
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief Send our rendering data to the VBO and IBO
	 * 
	 */
	void FontBatcher::BufferData()
	{
		_vBO.SetData(&_glyphVertices[0], _glyphVertices.size(), 0);
		_iBO.SetData(&_glyphIndices[0], _glyphIndices.size(), 0);
		_glyphVertices.clear();
		_glyphIndices.clear();
		_bufferedChars = _unbufferedChars;
		_unbufferedChars = 0;
	}

	void FontBatcher::generateGlyphPrimitive(const char glyph, int xOffset, int yOffset)
	{
		if (!_fontAtlas)
		{
			throw std::exception();
		}
		const GlyphSubtexture& glyphSub = _fontAtlas->GetCharUV(glyph);
		xOffset += glyphSub.XOffset;
		yOffset -= glyphSub.YOffset;
		unsigned int currentIndex = _glyphVertices.size();
		// Top left
		_glyphVertices.emplace_back(VertexPositionTexture(Vector2(xOffset, yOffset), Vector2(glyphSub.X, glyphSub.Y)));
		// Top right
		_glyphVertices.emplace_back(VertexPositionTexture(Vector2(xOffset + glyphSub.PxW, yOffset), Vector2(glyphSub.X + glyphSub.W, glyphSub.Y)));
		// Bottom left
		_glyphVertices.emplace_back(VertexPositionTexture(Vector2(xOffset, static_cast<float>(yOffset) + glyphSub.PxH), Vector2(glyphSub.X, glyphSub.Y + glyphSub.H)));
		// Bottom right
		_glyphVertices.emplace_back(VertexPositionTexture(Vector2(xOffset + glyphSub.PxW, static_cast<float>(yOffset) + glyphSub.PxH), Vector2(glyphSub.X + glyphSub.W, glyphSub.Y + glyphSub.H)));
		unsigned int a = currentIndex;
		unsigned int b = currentIndex + 1;
		unsigned int c = currentIndex + 2;
		unsigned int d = currentIndex + 3;
		_glyphIndices.insert(_glyphIndices.end(), {c, b, a, d, b, c});
	}
}