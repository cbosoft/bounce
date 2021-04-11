#include "circle.hpp"
#include "../../renderer.hpp"

void CircleRenderable::draw()
{
    Renderer &renderer = Renderer::get();
    auto *obj = this->get_object();
    arma::vec2 cpos = obj->get_position();
    auto r = float(obj->get_radius());
    float x = cpos[0], y = cpos[1];

    constexpr int n = 100;
    constexpr float dtheta = 2.0*M_PI/double(n);
    float theta = 0.0;

    const Colour &colour = obj->get_colour();
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
    GLuint shader = renderer.get_shader("default");
    glUseProgram(shader);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, x)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, r)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, s)));
    glEnableVertexAttribArray(2);

    int loc = glGetUniformLocation(shader, "centre");
    if (loc != -1) glUniform2f(loc, x, y);
    loc = glGetUniformLocation(shader, "radius");
    if (loc != -1) glUniform1f(loc, r);

    glDrawArrays(GL_TRIANGLE_FAN, 0, n+1);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}