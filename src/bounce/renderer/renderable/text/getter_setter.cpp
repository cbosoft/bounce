#include <bounce/renderer/renderable/text/text.hpp>

void TextRenderable::set_font_name(const std::string &font_name)
{
    this->_font_name = font_name;
    this->refresh_font();
}

void TextRenderable::set_font_size(int font_size)
{
    this->_font_size = font_size;
    this->refresh_font();
}

void TextRenderable::set_text(const std::wstring &text)
{
    this->_text = text;
}

void TextRenderable::set_text(const std::string &text)
{
    this->_text = std::wstring(text.begin(), text.end());
}

const std::string &TextRenderable::get_font_name() const
{
    return this->_font_name;
}

const std::wstring &TextRenderable::get_text() const
{
    return this->_text;
}

int TextRenderable::get_font_size() const
{
    return this->_font_size;
}

void TextRenderable::set_alignment(TextHAlign h_align, TextVAlign v_align)
{
    this->_h_align = h_align;
    this->_v_align = v_align;
}

float TextRenderable::get_typeset_width() const
{
    return this->_typesetting_width;
}

void TextRenderable::set_typeset_width(float v)
{
    this->_typesetting_width = v;
}

float TextRenderable::get_line_spacing() const
{
    return this->_line_spacing;
}

void TextRenderable::set_line_spacing(float line_spacing)
{
    this->_line_spacing = line_spacing;
}
