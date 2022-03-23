#pragma once

namespace Ceres
{
	struct GlyphSubtexture
	{
		GlyphSubtexture(float x, float y, float w, float h)
			:X(x), Y(y), W(w), H(h)
		{
		}
		GlyphSubtexture() 
		{
		}

		float X = {};
		float Y = {};
		float W = {};
		float H = {};
		unsigned int PxW {};
		unsigned int PxH {};
		float XOffset {};
		float YOffset {};
		float Advance {};
	};
}