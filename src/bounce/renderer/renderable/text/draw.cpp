#include <bounce/renderer/renderable/text/text.hpp>
#include <bounce/renderer/font/manager/manager.hpp>

arma::vec2 TextRenderable::aligned_origin() const
{
    arma::vec2 rv = this->get_position();
    arma::vec2 text_size = this->measure();
    float line_height = 0;
    for (auto c : this->_text) {
        auto ch = this->_font->get_char(c);
        if (ch->bearing_y > line_height)
            line_height = ch->bearing_y;
    }
    switch (this->_h_align) {
        case HA_left:
            // nothing to do
            break;
        case HA_centre:
            rv[0] -= text_size[0]/2;
            break;
        case HA_right:
            rv[0] -= text_size[0];
            break;
    }
    switch (this->_v_align) {
        case VA_bottom:
            rv[1] += text_size[1];
            rv[1] -= line_height;
            break;
        case VA_centre:
            rv[1] += text_size[1]/2;
            rv[1] -= line_height;
            break;
        case VA_top:
            rv[1] -= line_height;
            break;
    }
    return rv;
}

void TextRenderable::draw() const
{
    Renderer &renderer = Renderer::get();
    GLuint shader = renderer.get_shader("font");
    glUseProgram(shader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, x)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, r)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, s)));
    glEnableVertexAttribArray(2);

    arma::vec2 origin = this->aligned_origin();

    float line_height = 0.f, width = 0.f;
    int idx_last_breaking_char = -1;
    auto fw = this->_typesetting_width;
    bool restricted_width = this->_typesetting_width > 0;
    std::vector<bool> breaks(this->_text.size(), false);
    for (int i = 0; i < int(this->_text.size()); i++) {
        auto c = this->_text[i];

        if (c == ' ') idx_last_breaking_char = i;
        auto ch = this->_font->get_char(c);
        if (ch->bearing_y > line_height)
            line_height = ch->bearing_y;
        if (restricted_width) {
            width += ch->advance;
            if (width > fw && idx_last_breaking_char > 0) {
                breaks[idx_last_breaking_char] = true;
                width = 0.f;
            }
        }

        if (c == '\n') {
            width = 0.f;
            breaks[i] = true;
        }
    }

    auto x = float(origin[0]);
    auto y = float(origin[1]);

    const Colour &colour = this->get_colour();
    float cr = colour.rf(), cg = colour.gf(), cb = colour.bf(), ca = colour.af();

    for (int i = 0; i < int(this->_text.size()); i++) {
        auto c = this->_text[i];
        if (c != '\n') {
            auto ch = this->_font->get_char(c);
            float h = ch->h, w = ch->w;
            float dy = ch->bearing_y - h, dx = ch->bearing_x;
            Vertex vertices[6];
            float xm = x + dx, ym = y + dy;

            vertices[0] = {xm, ym + h, 0.0f, cr, cg, cb, ca, 0.f, 0.f};
            vertices[1] = {xm, ym, 0.0f, cr, cg, cb, ca, 0.f, 1.f};
            vertices[2] = {xm + w, ym, 0.0f, cr, cg, cb, ca, 1.f, 1.f};

            vertices[3] = {xm + w, ym, 0.0f, cr, cg, cb, ca, 1.f, 1.f};
            vertices[4] = {xm + w, ym + h, 0.0f, cr, cg, cb, ca, 1.f, 0.f};
            vertices[5] = {xm, ym + h, 0.0f, cr, cg, cb, ca, 0.f, 0.f};

            x += ch->advance;

            glBindTexture(GL_TEXTURE_2D, ch->texture_id);
            glBindBuffer(GL_ARRAY_BUFFER, renderer.get_vbuf());
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        if (breaks[i]) {
            x = float(origin[0]);
            y -= line_height*_line_spacing;
        }
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
