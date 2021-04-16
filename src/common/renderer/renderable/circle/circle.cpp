#include "circle.hpp"
#include "../../renderer.hpp"

void CircleRenderable::draw() const
{
    Renderer &renderer = Renderer::get();
    arma::vec2 opos = this->get_position();

    float x = float(opos[0]);
    float y = float(opos[1]);
    float r = float(this->get_scale());

    constexpr int n = 100;
    constexpr float dtheta = 2.0*M_PI/double(n);
    float theta = 0.0;

    const Colour &colour = this->get_colour();
    float cr = colour.rf(), cg = colour.gf(), cb = colour.bf();

    Vertex vertices[(n + 1)];

    vertices[0] = {
            x, y, 0.0f,
            cr, cg, cb, 1.0f,
            0.5f, 0.5f
    };
    for (int i = 0; i <= n; i++) {
        const float c = std::cos(theta);
        const float s = std::sin(theta);
        vertices[i] = {
                x + r*c, y + r*s, 0.0f,
                cr, cg, cb, 1.0f,
                0.5f + 0.5f*c, 0.5f + 0.5f*s
        };
        theta += dtheta;
    }
    glBindBuffer(GL_ARRAY_BUFFER, renderer.get_vbuf());
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_DYNAMIC_DRAW);

    GLuint shader = renderer.get_shader(this->get_shader_name());
    if (this->has_texture()) {
        renderer.get_texture(this->get_texture_name())->use();
        shader = renderer.get_shader("sprite");
    }
    glUseProgram(shader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, x)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, r)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, s)));
    glEnableVertexAttribArray(2);

    // update uniforms
    int loc = glGetUniformLocation(shader, "centre");
    if (loc != -1) glUniform2f(loc, x, y);
    loc = glGetUniformLocation(shader, "radius");
    if (loc != -1) glUniform1f(loc, r);

    glDrawArrays(GL_TRIANGLE_FAN, 0, n+1);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}