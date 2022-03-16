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
			void LoadString(std::string string, unsigned int xPos, unsigned int yPos);

			unsigned int GetTriCount() const;

		private:
			void generateGlyphPrimitive(const char glyph, unsigned int xOffset, unsigned int yOffset);

			IndexBuffer _iBO;
			VertexArrayObject _vAO;
			VertexBufferObject _vBO;
			AssetPtr<FontAtlas> _fontAtlas;
			AssetPtr<Effect> _spriteEffect;

			std::vector<VertexPositionTexture> _glyphVertices;
			std::vector<unsigned int> _glyphIndices;
	};
}