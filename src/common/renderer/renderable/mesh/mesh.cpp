#include "mesh.hpp"
#include "../../renderer.hpp"

MeshRenderable::MeshRenderable(const std::vector<arma::vec2> &points)
:   points(points)
{
    // do nothing
}

void MeshRenderable::set_alignment(MeshRenderable_HorizontalAnchor ha, MeshRenderable_VerticalAnchor va)
{
    const double f = 1.0;
    switch (ha)
    {
        case MR_HA_CENTRE:
            this->_anchor[0] = 0.0;
            break;

        case MR_HA_LEFT:
            this->_anchor[0] = f;
            break;

        case MR_HA_RIGHT:
            this->_anchor[0] = -f;
            break;
    }
    switch (va)
    {
        case MR_VA_CENTRE:
            this->_anchor[1] = 0.0;
            break;

        case MR_VA_BOTTOM:
            this->_anchor[1] = f;
            break;

        case MR_VA_TOP:
            this->_anchor[1] = -f;
            break;
    }
}

void MeshRenderable::draw() const
{
    Renderer &renderer = Renderer::get();
    arma::vec2 opos = this->get_position();

    auto s = float(this->get_scale());
    auto x = float(opos[0]) + float(this->_anchor[0])*s;
    auto y = float(opos[1]) + float(this->_anchor[1])*s;

    const int n = int(this->points.size());

    Colour colour = this->get_border_colour();
    float r = colour.rf(), g = colour.gf(), b = colour.bf();
    auto border_size = (float)this->get_border_size();

    // first draw a mesh border_size bigger than the mesh
    std::vector<Vertex> vertices;
    for (int i = 0; i < n; i++) {
        auto dx = float(this->points[i][0]);
        auto dy = float(this->points[i][1]);
        if (dx < 0) dx -= border_size;
        if (dx > 0) dx += border_size;
        if (dy < 0) dy -= border_size;
        if (dy > 0) dy += border_size;
        vertices.push_back({
                x + dx * s, y + dy * s, 0.0f,
                r, g, b, 1.0f,
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
    if (loc != -1) glUniform1f(loc, s);
    loc = glGetUniformLocation(shader, "object_angle");
    if (loc != -1) glUniform1f(loc, float(this->get_angle()));

    glDrawArrays(GL_TRIANGLE_FAN, 0, int(vertices.size()));

    // draw main part of mesh
    shader = renderer.get_shader(this->get_shader_name());
    if (this->has_texture()) {
        renderer.get_texture(this->get_texture_name())->use();
        shader = renderer.get_shader("sprite");
    }
    glUseProgram(shader);

    loc = glGetUniformLocation(shader, "centre");
    if (loc != -1) glUniform2f(loc, x, y);
    loc = glGetUniformLocation(shader, "radius");
    if (loc != -1) glUniform1f(loc, s);
    loc = glGetUniformLocation(shader, "object_angle");
    if (loc != -1) glUniform1f(loc, float(this->get_angle()));
    colour = this->get_colour();
    r = colour.rf(); g = colour.gf(); b = colour.bf();
    for (int i = 0; i < n; i++) {
        const auto dx = float(this->points[i][0]);
        const auto dy = float(this->points[i][1]);
        vertices[i] = {
                x + dx * s, y + dy * s, 0.0f,
                r, g, b, 1.0f,
                0.5f + dx/2.0f, 0.5f + dy/2.0f
        };
    }
    //glBindBuffer(GL_ARRAY_BUFFER, renderer.get_vbuf());
    glBufferData(GL_ARRAY_BUFFER, long(vertices.size()*sizeof(Vertex)), &vertices[0], GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_FAN, 0, int(vertices.size()));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}