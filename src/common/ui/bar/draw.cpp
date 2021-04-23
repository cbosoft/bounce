#include "bar.hpp"
#include "../../renderer/renderer.hpp"

void BarGraph::draw() const
{
    RectangleMeshRenderable::draw();

    Renderer &renderer = Renderer::get();
    arma::vec2 opos = this->get_position();

    auto size = this->get_size();
    auto sx = float(size[0]);
    auto sy = float(size[1]);
    auto x = float(opos[0]) + float(this->_anchor[0])*sx;
    auto y = float(opos[1]) + float(this->_anchor[1])*sy;

    // first draw a mesh border_size bigger than the mesh
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, x)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, r)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, s)));
    glEnableVertexAttribArray(2);

    // draw main part of mesh
    GLuint shader = renderer.get_shader(this->get_shader_name());
    if (this->has_texture()) {
        renderer.get_texture(this->get_texture_name())->use();
        shader = renderer.get_shader("sprite");
    }
    glUseProgram(shader);

    int loc = glGetUniformLocation(shader, "centre");
    if (loc != -1) glUniform2f(loc, x, y);
    loc = glGetUniformLocation(shader, "radius");
    if (loc != -1) glUniform1f(loc, sx);
    loc = glGetUniformLocation(shader, "object_angle");
    if (loc != -1) glUniform1f(loc, float(this->get_angle()));
    const Colour &colour = Colours::red;
    float r = colour.rf(), g = colour.gf(), b = colour.bf();

    const auto extent = float(this->measure_value()/this->measure_maximum());
    std::vector<arma::vec2> bar = {
            {0, -.5}, {0, .5},
            {1, .5}, {1, -.5}
    };
    std::vector<Vertex> vertices;
    for (int i = 0; i < 4; i++) {
        const auto dx = float(bar[i][0]);
        const auto dy = float(bar[i][1]);
        vertices.push_back({
                x + (dx*extent - .5f)*sx, y + dy*sy, 0.0f,
                r, g, b, 1.0f,
                0.5f + dx/2.0f, 0.5f + dy/2.0f
        });
    }
    glBufferData(GL_ARRAY_BUFFER, long(vertices.size()*sizeof(Vertex)), &vertices[0], GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_FAN, 0, int(vertices.size()));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}
