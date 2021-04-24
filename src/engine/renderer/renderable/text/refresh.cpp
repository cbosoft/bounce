#include "text.hpp"
#include "../../font/manager/manager.hpp"

void TextRenderable::refresh_font()
{
    this->_font = FontManager::ref().get_font(this->_font_name, this->_font_size);
}