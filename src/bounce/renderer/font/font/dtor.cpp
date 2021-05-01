#include <bounce/renderer/font/font/font.hpp>

Font::~Font()
{
    FT_Done_Face(this->_face);
}