#include "text.hpp"
#include "../../font/font/font.hpp"
#include "../../font/manager/manager.hpp"

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

    arma::vec2 bl = this->get_position();
    auto x = float(bl[0]);
    auto y = float(bl[1]);

    const Colour &colour = this->get_colour();
    float cr = colour.rf(), cg = colour.gf(), cb = colour.bf();

    for (auto c : this->_text) {
        auto ch = this->_font->get_char(c);
        float h = ch->h, w = ch->w;
        float dy = ch->bearing_y - h, dx = ch->bearing_x;
        Vertex vertices[4];
        float xm = x+dx, ym = y+dy;

        vertices[0] = {xm,   ym,   0.0f, cr, cg, cb, 1.0f, 0.f, 1.f};
        vertices[1] = {xm,   ym+h, 0.0f, cr, cg, cb, 1.0f, 0.f, 0.f};
        vertices[2] = {xm+w, ym+h, 0.0f, cr, cg, cb, 1.0f, 1.f, 0.f};
        vertices[3] = {xm+w, ym,   0.0f, cr, cg, cb, 1.0f, 1.f, 1.f};

        x += ch->advance;

        glBindTexture(GL_TEXTURE_2D, ch->texture_id);
        glBindBuffer(GL_ARRAY_BUFFER, renderer.get_vbuf());
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}