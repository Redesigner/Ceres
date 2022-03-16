#include "FontAtlas.h"

#include <fmt/core.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H

const std::string FONT_DIR = "C:\\WINDOWS\\Fonts\\";

namespace Ceres
{
	FontAtlas::FontAtlas(std::string name, unsigned int resolution, unsigned int fontSize)
	{
		FT_Library fontLibrary = nullptr;
        FT_Error error = FT_Init_FreeType(&fontLibrary);
        if (error)
        {
            // printPrefix();
            fmt::print("Failed to initialize freetype.\n");
        }
        else
        {
            // printPrefix();
            fmt::print("FreeType library initialized.\n");
        }
        const unsigned int textureWidth = resolution;
        const unsigned int textureHeight = resolution;

        const float textureResolutionX = 1 / static_cast<float>(textureWidth);
        const float textureResolutionY = 1 / static_cast<float>(textureHeight);
        std::string arialPath = FONT_DIR + name;
        FT_Face face = nullptr;
        FT_New_Face(fontLibrary, arialPath.c_str(), 0, &face);
        FT_Set_Pixel_Sizes(face, fontSize, 0);
        FT_GlyphSlot glyphSlot = face->glyph;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &_openGLTextureID);
        glBindTexture(GL_TEXTURE_2D, _openGLTextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, textureHeight, textureWidth, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        FT_UInt currentX = 0;
        FT_UInt currentY = 0;
        FT_UInt currentH = 0;
        for (FT_ULong i = 0; i < 256; i++)
        {
            FT_UInt glyphIndex = FT_Get_Char_Index(face, i);
            FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
            FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

            FT_UInt width = glyphSlot->bitmap.width;
            FT_UInt height = glyphSlot->bitmap.rows;

            if (currentX + width >= textureWidth)
            {
                currentX = 0;
                currentY += currentH;
                currentH = 0;
            }
            if (currentY + width >= textureHeight)
            {
                // printPrefix();
                fmt::print("Unable to generate font texture, not enough texture space.\n");
                break;
            }
            glTexSubImage2D(GL_TEXTURE_2D, 0,
                currentX, currentY,
                width, height,
                GL_RED, GL_UNSIGNED_BYTE, glyphSlot->bitmap.buffer);
            _glyphSubs[i] = GlyphSubtexture(
                currentX * textureResolutionX, currentY * textureResolutionY,
                width * textureResolutionX, height * textureResolutionY);
            _glyphSubs[i].pxH = height;
            _glyphSubs[i].pxW = width;

            currentX += width;
            if (height > currentH)
            {
                currentH = height;
            }
        }
        FT_Done_Face(face);
        FT_Done_Library(fontLibrary);
	}

    FontAtlas::FontAtlas(FontAtlas&& fontAtlas)
    {
        _openGLTextureID = fontAtlas._openGLTextureID;
        std::swap(fontAtlas._glyphSubs, _glyphSubs);
        fontAtlas._initialized = false;
    }

    FontAtlas::~FontAtlas()
    {
        if(_initialized)
        {
            glDeleteTextures(1, &_openGLTextureID);
        }
    }

    const GlyphSubtexture& FontAtlas::GetCharUV(char glyph) const
    {
        return _glyphSubs[static_cast<int>(glyph)];
    }

    GLuint FontAtlas::GetTextureID() const
    {
        return _openGLTextureID;
    }
}