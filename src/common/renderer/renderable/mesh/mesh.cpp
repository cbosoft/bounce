#include "mesh.hpp"
#include "../../renderer.hpp"

MeshRenderable::MeshRenderable(const std::vector<arma::vec2> &points)
: points(points)
{
    // do nothing
}

void MeshRenderable::draw() const
{
    Renderer &renderer = Renderer::get();
    auto obj = this->get_object();
    arma::vec2 opos = this->get_position();

    auto x = float(opos[0]);
    auto y = float(opos[1]);
    auto r = float(this->get_scale());

    const int n = int(this->points.size());

    const Colour &colour = obj->get_colour();
    float cr = colour.rf(), cg = colour.gf(), cb = colour.bf();

    std::vector<Vertex> vertices;
    for (int i = 0; i < n; i++) {
        const auto dx = float(this->points[i][0]);
        const auto dy = float(this->points[i][1]);
        vertices.push_back({
                x + dx*r, y + dy*r, 0.0f,
                cr, cg, cb, 1.0f,
                0.5f + dx/2.0f, 0.5f + dy/2.0f
        });
    }
    glBindBuffer(GL_ARRAY_BUFFER, renderer.get_vbuf());
    glBufferData(GL_ARRAY_BUFFER, long(vertices.size()*sizeof(Vertex)), &vertices[0], GL_DYNAMIC_DRAW);

    GLuint shader = renderer.get_shader("default");
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

    glDrawArrays(GL_TRIANGLE_FAN, 0, int(vertices.size()));
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}