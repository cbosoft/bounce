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

    this->update_shader_uniforms();

    glClear(GL_COLOR_BUFFER_BIT);
    this->render_background();
    for (auto *object : this->objects) {
        auto *rbl = object->get_renderable();
        if (rbl) rbl->draw();
    }

    glfwSwapBuffers(this->window);
    glfwPollEvents();
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


void Renderer::update_shader_uniforms() const
{
    for (const auto &kv : this->shaders) {
        GLuint shader_id = kv.second;
        glUseProgram(shader_id);
        int loc = glGetUniformLocation(shader_id, "time");
        if (loc != -1) glUniform1f(loc, float(PhysicsEngine::engine().get_time()));

        loc = glGetUniformLocation(shader_id, "camera_position");
        auto cp = this->camera_transform.get_position();
        if (loc != -1) glUniform2f(loc, float(cp[0]), float(cp[1]));

        loc = glGetUniformLocation(shader_id, "camera_size");
        auto cs = this->camera_size;
        if (loc != -1) glUniform2f(loc, float(cs[0]), float(cs[1]));
    }
}