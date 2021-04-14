#include "font.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Font::Font(FT_Face face, int height)
{
    FT_Set_Pixel_Sizes(face, 0, height);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (char c = 0; c < 127; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "char '" << c << "' not in font." << std::endl;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0, GL_RED,
                int(face->glyph->bitmap.width),
                int(face->glyph->bitmap.rows),
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        constexpr float mult = 0.1f;
        this->chars[c] = new Character({
                texture,
                float(face->glyph->bitmap.width)*mult,
                float(face->glyph->bitmap.rows)*mult,
                float(face->glyph->bitmap_left)*mult,
                float(face->glyph->bitmap_top)*mult,
                float(face->glyph->advance.x)*mult / float(1 << 6)
        });
    }

    FT_Done_Face(face);
}