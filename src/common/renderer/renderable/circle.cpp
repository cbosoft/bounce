#include "circle.hpp"
#include "../renderer.hpp"

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

    GLfloat vertex_buffer_data[(n+1)*6] = {0.0f};
    vertex_buffer_data[0] = x;
    vertex_buffer_data[1] = y;
    vertex_buffer_data[2] = 0.0f;
    vertex_buffer_data[3] = cr;
    vertex_buffer_data[4] = cg;
    vertex_buffer_data[5] = cb;
    for (int i = 0; i <= n; i++) {
        vertex_buffer_data[i*6 + 0] = x + r*std::cos(theta);
        vertex_buffer_data[i*6 + 1] = y + r*std::sin(theta);
        vertex_buffer_data[i*6 + 2] = 0.0f;
        vertex_buffer_data[i*6 + 3] = cr;
        vertex_buffer_data[i*6 + 4] = cg;
        vertex_buffer_data[i*6 + 5] = cb;
        theta += dtheta;
    }
    glBindBuffer(GL_ARRAY_BUFFER, renderer.get_vbuf());
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_DYNAMIC_DRAW);
    GLuint shader = renderer.get_shader("default");
    glUseProgram(shader);
    int loc = glGetUniformLocation(shader, "centre");
    if (loc != -1) glUniform2f(loc, x, y);
    loc = glGetUniformLocation(shader, "radius");
    if (loc != -1) glUniform1f(loc, r);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, n+1);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}