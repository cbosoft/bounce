#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <bounce/renderer/font/font/font.hpp>

void Font::load_char_from_font(unsigned long charcode)
{
    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FT_UInt glyph_index = FT_Get_Char_Index(this->_face, charcode);

    if (FT_Load_Glyph(this->_face, glyph_index, FT_LOAD_RENDER)) {
        std::cerr << "char '" << wchar_t(charcode) << "' not in font." << std::endl;
        return;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
            GL_TEXTURE_2D,
            0, GL_RED,
            int(this->_face->glyph->bitmap.width),
            int(this->_face->glyph->bitmap.rows),
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            this->_face->glyph->bitmap.buffer);

    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    constexpr float mult = 0.1f;
    this->chars[charcode] = new Character({
        texture,
        float(this->_face->glyph->bitmap.width)*mult,
        float(this->_face->glyph->bitmap.rows)*mult,
        float(this->_face->glyph->bitmap_left)*mult,
        float(this->_face->glyph->bitmap_top)*mult,
        float(this->_face->glyph->advance.x)*mult / float(1 << 6)
    });

    // restore unpack alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}