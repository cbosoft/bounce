#include <bounce/renderer/renderable/text/text.hpp>

TextRenderable::TextRenderable(const std::string &text, const std::string &font_name, int font_size, float typeset_width)
:   TextRenderable(std::wstring(text.begin(), text.end()), font_name, font_size, typeset_width)
{
    // do nothing
}

TextRenderable::TextRenderable(const std::wstring &text, const std::string &font_name, int font_size, float typeset_width)
        :   Renderable()
        ,   _font(nullptr)
        ,   _text(text)
        ,   _font_name(font_name)
        ,   _font_size(font_size)
        ,   _typesetting_width(typeset_width)
        ,   _line_spacing(1.1)
        ,   _v_align(VA_centre)
        ,   _h_align(HA_centre)
{
    this->refresh_font();
}
