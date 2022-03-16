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
        _spriteEffect->SetMatrix2D("transform", Matrix2D::Sprite(
			0, 0,
            1, -1,
            1280, 720));
		}

	void FontBatcher::LoadString(std::string string, unsigned int xPos, unsigned int yPos)
	{
		unsigned int currentX = xPos;
		for (int i = 0; i < string.length(); i++)
		{
			generateGlyphPrimitive(string[i], currentX, yPos);
			currentX += _fontAtlas->GetCharUV(string[i]).pxW; 
		}
		_vBO.SetData(&_glyphVertices[0], _glyphVertices.size());
		_iBO.SetData(&_glyphIndices[0], _glyphIndices.size());
		// _glyphVertices.clear();
		// _glyphIndices.clear();
	}

	unsigned int FontBatcher::GetTriCount() const
	{
		return _glyphIndices.size();
	}

	void FontBatcher::generateGlyphPrimitive(const char glyph, unsigned int xOffset, unsigned int yOffset)
	{
		if (!_fontAtlas)
		{
			throw std::exception();
		}
		const GlyphSubtexture& glyphSub = _fontAtlas->GetCharUV(glyph);
		unsigned int currentIndex = _glyphVertices.size();
		// Top left
		_glyphVertices.emplace_back(VertexPositionTexture(Vector2(xOffset, yOffset), Vector2(glyphSub.X, glyphSub.Y + glyphSub.H)));
		// Top right
		_glyphVertices.emplace_back(VertexPositionTexture(Vector2(xOffset + glyphSub.pxW, yOffset), Vector2(glyphSub.X + glyphSub.W, glyphSub.Y + glyphSub.H)));
		// Bottom left
		_glyphVertices.emplace_back(VertexPositionTexture(Vector2(xOffset, yOffset - glyphSub.pxH), Vector2(glyphSub.X, glyphSub.Y)));
		// Bottom right
		_glyphVertices.emplace_back(VertexPositionTexture(Vector2(xOffset + glyphSub.pxW, yOffset - glyphSub.pxH), Vector2(glyphSub.X + glyphSub.W, glyphSub.Y)));
		unsigned int a = currentIndex;
		unsigned int b = currentIndex + 1;
		unsigned int c = currentIndex + 2;
		unsigned int d = currentIndex + 3;
		_glyphIndices.insert(_glyphIndices.end(), {a, b, c, c, b, d});
	}
}