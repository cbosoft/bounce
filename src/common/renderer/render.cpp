#include "renderer.hpp"
#include "../physics/engine/engine.hpp"

GLFWwindow  *Renderer::get_window()
{
    return this->window;
}

void Renderer::render()
{
    int w, h;
    glfwGetWindowSize(this->window, &w, &h);
    this->set_window_size(w, h);
    glViewport(0, 0, w*2, h*2);
    this->set_camera_diagonal(150.0);

    this->update_shader_uniforms();
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w*2, h*2, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, this->txt, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(this->varr);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbuf);
    this->render_background();
    for (auto *object : this->objects) {
        auto *rbl = object->get_renderable();
        if (rbl) rbl->draw();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, w*2, h*2);
    GLuint shader_id = this->shaders["quad"];
    glUseProgram(shader_id);
    this->set_shader_filter_kernel(shader_id, 0.0625, {1, 2, 1, 2, 4, 2, 1, 2, 1});
    glBindTexture(GL_TEXTURE_2D, this->txt);
    glBindVertexArray(this->qarr);
    glBindBuffer(GL_ARRAY_BUFFER, this->qbuf);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void *)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void *)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 6);

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

        loc = glGetUniformLocation(shader_id, "camera_angle");
        if (loc != -1) glUniform1f(loc, this->camera_angle);
    }
}

void Renderer::set_shader_filter_kernel(GLuint shader_id, float kernel_norm, const std::array<float, 9> &args)
{
    int loc = glGetUniformLocation(shader_id, "kernel_norm");
    if (loc != -1) glUniform1f(loc, kernel_norm);
    loc = glGetUniformLocation(shader_id, "kernel_a");
    if (loc != -1) glUniform3f(loc, args[0], args[1], args[2]);
    loc = glGetUniformLocation(shader_id, "kernel_b");
    if (loc != -1) glUniform3f(loc, args[3], args[4], args[5]);
    loc = glGetUniformLocation(shader_id, "kernel_c");
    if (loc != -1) glUniform3f(loc, args[6], args[7], args[8]);
}
