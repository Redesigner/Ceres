#pragma once

#include "Effect.h"
#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "VertexTypes/VertexPositionTexture.h"

#include "../Common/AssetPointer.h"

#include "../IO/FontLoading/FontAtlas.h"

#include <array>
#include <string>


namespace Ceres
{
	using GlyphPrimitive = std::array<VertexPositionTexture, 4>; 
	class FontBatcher
	{
		public:
			FontBatcher(unsigned int size, AssetPtr<FontAtlas> fontAtlas, AssetPtr<Effect> spriteEffect);
			FontBatcher(FontBatcher&) = delete;
			FontBatcher(FontBatcher&& fontBatcher);
			~FontBatcher();

			void Bind();
			void SetScreenSize(unsigned int x, unsigned int y);
			void LoadString(std::string string, int xPos, int yPos);

			unsigned int GetTriCount() const;

		private:
			void generateGlyphPrimitive(const char glyph, int xOffset, int yOffset);

			IndexBuffer _iBO;
			VertexArrayObject _vAO;
			VertexBufferObject _vBO;
			AssetPtr<FontAtlas> _fontAtlas;
			AssetPtr<Effect> _spriteEffect;

			std::vector<VertexPositionTexture> _glyphVertices;
			std::vector<unsigned int> _glyphIndices;
			unsigned int _charCount = 0;

			Matrix2D _screenSpace;
	};
}