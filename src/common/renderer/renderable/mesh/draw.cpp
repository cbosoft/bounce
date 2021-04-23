#include "mesh.hpp"
#include "../../renderer.hpp"


void MeshRenderable::draw() const
{
    if (this->get_border_size() > 1e-2)
        this->draw_border();
    this->draw_main();
}


void MeshRenderable::draw_border() const
{
    Renderer &renderer = Renderer::get();
    arma::vec2 opos = this->get_position(), scale = this->get_size();

    auto sx = float(scale[0]), sy = float(scale[1]);
    auto x = float(opos[0]) + float(this->_anchor[0])*sx;
    auto y = float(opos[1]) + float(this->_anchor[1])*sy;

    const int n = int(this->_points.size());

    Colour colour = this->get_border_colour();
    float r = colour.rf(), g = colour.gf(), b = colour.bf(), a = colour.af();
    auto border_size = (float)this->get_border_size();

    // first draw a mesh border_size bigger than the mesh
    std::vector<Vertex> vertices;
    for (int i = 0; i < n; i++) {
        auto dx = float(this->_points[i][0]);
        auto dy = float(this->_points[i][1]);
        float bx = (dx < 0.0 ? -1.f : 1.f)*border_size;
        float by = (dy < 0.0 ? -1.f : 1.f)*border_size;
        vertices.push_back({
            x + bx + dx * sx, y + by + dy * sy, 0.0f,
            r, g, b, a,
            0.5f + dx/2.0f, 0.5f + dy/2.0f
        });
    }
    glBindBuffer(GL_ARRAY_BUFFER, renderer.get_vbuf());
    glBufferData(GL_ARRAY_BUFFER, long(vertices.size()*sizeof(Vertex)), &vertices[0], GL_DYNAMIC_DRAW);

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
    if (loc != -1) glUniform1f(loc, sx);
    loc = glGetUniformLocation(shader, "object_angle");
    if (loc != -1) glUniform1f(loc, float(this->get_angle()));

    glDrawArrays(GL_TRIANGLE_FAN, 0, int(vertices.size()));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void MeshRenderable::draw_main() const
{
    Renderer &renderer = Renderer::get();
    arma::vec2 opos = this->get_position(), scale = this->get_size();

    auto sx = float(scale[0]), sy = float(scale[1]);
    auto x = float(opos[0]) + float(this->_anchor[0])*sx;
    auto y = float(opos[1]) + float(this->_anchor[1])*sy;

    const int n = int(this->_points.size());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, x)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, r)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, s)));
    glEnableVertexAttribArray(2);

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
    const Colour &colour = this->get_colour();
    float r = colour.rf(), g = colour.gf(), b = colour.bf(), a = colour.af();

    std::vector<Vertex> vertices;
    for (int i = 0; i < n; i++) {
        const auto dx = float(this->_points[i][0]);
        const auto dy = float(this->_points[i][1]);
        vertices.push_back({
                x + dx * sx, y + dy * sy, 0.0f,
                r, g, b, a,
                0.5f + dx/2.0f, 0.5f + dy/2.0f
        });
    }
    glBufferData(GL_ARRAY_BUFFER, long(vertices.size()*sizeof(Vertex)), &vertices[0], GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_FAN, 0, int(vertices.size()));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}
