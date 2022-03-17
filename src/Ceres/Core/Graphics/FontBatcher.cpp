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
		_vBO.SetData(&_glyphVertices[0], _glyphVertices.size());
		_iBO.SetData(&_glyphIndices[0], _glyphIndices.size());
		_glyphVertices.clear();
		_glyphIndices.clear();
		_charCount = string.size(); 
	}

	unsigned int FontBatcher::GetTriCount() const
	{
		return _charCount * 6;
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