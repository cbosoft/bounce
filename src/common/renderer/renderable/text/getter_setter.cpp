#include "text.hpp"

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

void TextRenderable::set_text(const std::string &text)
{
    this->_text = text;
}

const std::string &TextRenderable::get_font_name() const
{
    return this->_font_name;
}

const std::string &TextRenderable::get_text() const
{
    return this->_text;
}

int TextRenderable::get_font_size() const
{
    return this->_font_size;
}
