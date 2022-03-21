#include "FontAtlas.h"

#include <fmt/core.h>
#include <fmt/color.h>

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
            printPrefix();
            fmt::print("Failed to initialize freetype.\n");
        }
        else
        {
            printPrefix();
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
        glClearTexImage(_openGLTextureID, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

        FT_UInt currentX = 0;
        FT_UInt currentY = 0;
        FT_UInt currentH = 0;
        const unsigned int padding = 1;
        for (int i = 0; i < 256; i++)
        {
            FT_UInt glyphIndex = FT_Get_Char_Index(face, i);
            FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
            FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
            if (_lineHeight == 0)
            {
                _lineHeight = static_cast<float>((face->size->metrics.ascender - face->size->metrics.descender) >> 6);            
            }

            FT_UInt width = glyphSlot->bitmap.width;
            FT_UInt height = glyphSlot->bitmap.rows;

            if (currentX + width >= textureWidth)
            {
                currentX = 0;
                currentY += currentH + padding * 2;
                currentH = 0;
            }
            if (currentY + width >= textureHeight)
            {
                printPrefix();
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
            _glyphSubs[i].PxH = height;
            _glyphSubs[i].PxW = width;
            _glyphSubs[i].XOffset = static_cast<float>(glyphSlot->bitmap_left);
            _glyphSubs[i].YOffset = static_cast<float>(glyphSlot->bitmap_top);
            _glyphSubs[i].Advance = static_cast<float>(glyphSlot->advance.x >> 6);

            currentX += width + padding * 2;
            if (height > currentH)
            {
                currentH = height;
            }
            FT_Vector kerning = FT_Vector();
            for (int j = 0; j < 256; j++)
            {
                FT_Get_Kerning(face, i, j, FT_KERNING_DEFAULT, &kerning);
                if (kerning.x != 0)
                {
                    KerningPair pair = KerningPair(i, j);
                    _kerningMap.emplace_back(pair, static_cast<float>(kerning.x >> 6));
                }
            }
        }
        printPrefix();
        fmt::print("Loaded font '{}' {}pt | reserved {}px\n", name, fontSize, resolution);
        FT_Done_Face(face);
        FT_Done_Library(fontLibrary);
	}

    FontAtlas::FontAtlas(FontAtlas&& fontAtlas)
    {
        _openGLTextureID = fontAtlas._openGLTextureID;
        _lineHeight = fontAtlas._lineHeight;
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
        if (glyph < 0 || glyph > 255)
        {
            glyph = 0;
        }
        return _glyphSubs[glyph];
    }

    float FontAtlas::GetKerning(char a, char b) const
    {
        KerningPair pair = KerningPair(a, b);
        for(std::pair<KerningPair, float> value : _kerningMap)
        {
            if (value.first == pair)
            {
                return value.second;
            }
        }
        return 0.0f;
    }

    GLuint FontAtlas::GetTextureID() const
    {
        return _openGLTextureID;
    }

    float FontAtlas::GetLineHeight() const
    {
        return _lineHeight;
    }

    void FontAtlas::printPrefix() const
    {
        fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "[FontAtlas] ");
    }
}