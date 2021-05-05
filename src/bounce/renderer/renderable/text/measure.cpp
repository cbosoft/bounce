#include <bounce/renderer/renderable/text/text.hpp>

arma::vec2 TextRenderable::measure() const
{
    float max_width = 0.f, width = 0.f, line_height = 0.f;
    bool restricted_width = this->_typesetting_width > 0;
    int nlines = 1;

    int idx_last_breaking_char = -1;
    std::vector<bool> breaks(this->_text.size(), false);
    for (int i = 0; i < int(this->_text.size()); i++) {
        auto c = this->_text[i];

        if (c == ' ') idx_last_breaking_char = i;
        auto ch = this->_font->get_char(c);
        if (ch->bearing_y > line_height)
            line_height = ch->bearing_y;
        if (restricted_width) {
            width += ch->advance;
            if (width > this->_typesetting_width && idx_last_breaking_char > 0) {
                breaks[idx_last_breaking_char] = true;
                width = 0.f;
            }
        }
    }

    for (int i = 0; i < int(this->_text.size()); i++) {
        auto c = this->_text[i];
        Character *ch = this->_font->get_char(c);
        width += ch->advance;
        if (restricted_width) {
            if (breaks[i]) {
                width = 0.0f;
                nlines ++;
            }
        }
        if (width > max_width) {
            max_width = width;
        }

        float p_height = ch->bearing_y;
        if (p_height > line_height) {
            line_height = p_height;
        }

    }
    float height = float(nlines)*line_height*this->_line_spacing;
    return {max_width, height};
}