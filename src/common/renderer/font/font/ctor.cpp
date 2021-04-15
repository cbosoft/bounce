#include "font.hpp"

Font::Font(FT_Face face, int height)
: _face(face)
{
    FT_Set_Pixel_Sizes(face, 0, height);
    for (unsigned long c = 0; c < 128; c++) {
        this->load_char_from_font(c);
    }
}