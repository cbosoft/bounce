#include "text.hpp"

arma::vec2 TextRenderable::measure() const
{
    float width = 0.0f, height = 0.0f;

    for (const char &c : this->_text) {
        Character *ch = this->_font->get_char(c);
        width += ch->advance;

        float p_height = ch->bearing_y;
        if (p_height > height) {
            height = p_height;
        }
    }

    return {width, height};
}