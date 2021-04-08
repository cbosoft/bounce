#include "renderer.hpp"
#include "../physics/engine/engine.hpp"

GLFWwindow  *Renderer::get_window()
{
    return this->window;
}

void Renderer::render()
{
    int h, w;
    glfwGetWindowSize(this->window, &h, &w);
    this->window_size[0] = double(w);
    this->window_size[1] = double(h);

    glClear(GL_COLOR_BUFFER_BIT);
    this->render_background();
    for (auto *object : this->objects) {
        this->render(object);
    }

    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void Renderer::render(PhysicsObject *object)
{
    (void) object;
    this->draw_circle(object->get_position(), object->get_radius());
}

void Renderer::render_background()
{
    GLfloat vertex_buffer_data[] = {
            -1.0f,-1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             1.0f,-1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,

             1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    };
    glUseProgram(this->shaders["background"]);
    int loc = glGetUniformLocation(this->shaders["background"], "time");
    if (loc != -1) glUniform1f(loc, float(PhysicsEngine::engine().get_time()));

    loc = glGetUniformLocation(this->shaders["background"], "camera_position");
    auto cp = this->camera_transform.get_position();
    if (loc != -1) glUniform2f(loc, float(cp[0]), float(cp[1]));

    loc = glGetUniformLocation(this->shaders["background"], "camera_size");
    auto cs = this->camera_size;
    if (loc != -1) glUniform2f(loc, float(cs[0]), float(cs[1]));

    glBindBuffer(GL_ARRAY_BUFFER, this->vbuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 3, 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}



void Renderer::draw_circle(const arma::vec2 &position, double radius)
{
    arma::vec2 cpos = position; //this->world_pt_to_screen_pt(position);
    auto r = float(radius); //float(this->world_len_to_screen_len(radius));
    float x = cpos[0], y = cpos[1];

    constexpr int n = 100;
    constexpr double dtheta = 2.0*M_PI/double(n);
    double theta = 0.0;

    GLfloat vertex_buffer_data[(n+1)*6] = {0.0f};
    vertex_buffer_data[0] = x;
    vertex_buffer_data[1] = y;
    vertex_buffer_data[2] = 0.0f;
    vertex_buffer_data[3] = 1.0f;
    vertex_buffer_data[4] = 0.5f;
    vertex_buffer_data[5] = 0.5f;
    for (int i = 0; i <= n; i++) {
        vertex_buffer_data[i*6 + 0] = x + r*std::cos(theta);
        vertex_buffer_data[i*6 + 1] = y + r*std::sin(theta);
        vertex_buffer_data[i*6 + 2] = 0.0f;
        vertex_buffer_data[i*6 + 3] = 0.6f;
        vertex_buffer_data[i*6 + 4] = 0.6f;
        vertex_buffer_data[i*6 + 5] = 0.6f;
        theta += dtheta;
    }
    glBindBuffer(GL_ARRAY_BUFFER, this->vbuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_DYNAMIC_DRAW);
    glUseProgram(this->shaders["default"]);
    int loc = glGetUniformLocation(this->shaders["default"], "camera_position");
    auto cp = this->camera_transform.get_position();
    if (loc != -1) glUniform2f(loc, float(cp[0]), float(cp[1]));

    loc = glGetUniformLocation(this->shaders["default"], "camera_size");
    auto cs = this->camera_size;
    if (loc != -1) glUniform2f(loc, float(cs[0]), float(cs[1]));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawArrays(GL_TRIANGLES, 3, 3);
    glDrawArrays(GL_TRIANGLE_FAN, 0, n+1);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}