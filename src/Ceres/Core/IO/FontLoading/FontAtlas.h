#pragma once

extern "C"
{
    #include <SDL2/SDL.h>
	#include <gl/glew.h>
}

#include "GlyphSubtexture.h"

#include <array>
#include <string>
#include <vector>

namespace Ceres
{
	class FontAtlas
	{
		public:
			FontAtlas(std::string name, unsigned int resolution, unsigned int fontSize);
			FontAtlas(FontAtlas&) = delete;
			FontAtlas(FontAtlas&& fontAtlas);
			~FontAtlas();

			const GlyphSubtexture& GetCharUV(char glyph) const;
			float GetKerning(char a, char b) const;

			GLuint GetTextureID() const;

		private:
			struct KerningPair
			{
				KerningPair(char a, char b)
					:_a(a), _b(b)
				{}
				char _a, _b;

				bool operator ==(KerningPair& pair)
				{
					return pair._a = _a && pair._b == _b;
				}
			};

			GLuint _openGLTextureID = 0;
			// Assuming we use UTF-8, cover all possible values
			std::array<GlyphSubtexture, 256> _glyphSubs;
			std::vector<std::pair<KerningPair, float>> _kerningMap; 


			bool _initialized = true;
	};
}