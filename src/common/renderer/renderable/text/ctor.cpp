#include "text.hpp"

TextRenderable::TextRenderable(const std::string &text, const std::string &font_name, int font_size)
:   Renderable()
,   _font(nullptr)
,   _text(text)
,   _font_name(font_name)
,   _font_size(font_size)
,   _v_align(VA_centre)
,   _h_align(HA_centre)
{
    this->refresh_font();
}