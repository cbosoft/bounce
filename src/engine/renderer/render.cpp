#include "renderer.hpp"
#include "../physics/engine/engine.hpp"
#include "../game/game.hpp"

GLFWwindow  *Renderer::get_window()
{
    return this->window;
}

bool Renderer::should_render()
{
    this->error_check("once-per-frame error check");
    auto now = _RDR_CLOCK_T::now();
    auto time_since = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->time_last_render);
    int us = int(time_since.count());
    if (us < this->_min_mspf) {
        return false;
    }

    this->_actual_fps = (this->_actual_fps + (1000/us))/2;
    this->time_last_render = now;

    return true;
}

void Renderer::render()
{
    if (!this->should_render()) {
        return;
    }

    // Call update action on transforms in active scene.
    this->game->get_active_scene()->update();
    this->update_shader_uniforms();

    this->set_target_to_texture(this->txt);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(this->varr);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbuf);

    // draw zsorted renderables
    Scene *scene = this->game->get_active_scene();
    if (scene) {
        std::list<const Renderable *> rbls;
        scene->get_renderables(rbls);
        rbls.sort(Renderable::z_sort);
        for (auto *rbl : rbls) {
            if (rbl && rbl->get_visible())
                rbl->draw();
        }
    }

    // draw quad to screen
    this->set_target_to_screen();
    glClear(GL_COLOR_BUFFER_BIT);
    GLuint shader_id = this->get_screen_effect();
    glUseProgram(shader_id);
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


void Renderer::update_shader_uniforms() const
{
    RectTransform *camera = this->game->get_active_scene()->get_active_camera();
    arma::vec2 position = camera->get_position(), size = camera->get_size(), w = this->window_size;
    for (const auto &kv : this->shaders) {
        GLuint shader_id = kv.second;
        glUseProgram(shader_id);
        int loc = glGetUniformLocation(shader_id, "time");
        if (loc != -1) glUniform1f(loc, float(PhysicsEngine::ref().get_time()));

        loc = glGetUniformLocation(shader_id, "camera_position");
        auto cp = position;
        if (loc != -1) glUniform2f(loc, float(cp[0]), float(cp[1]));

        loc = glGetUniformLocation(shader_id, "camera_size");
        auto cs = size;
        if (loc != -1) glUniform2f(loc, float(cs[0]), float(cs[1]));

        loc = glGetUniformLocation(shader_id, "camera_angle");
        if (loc != -1) glUniform1f(loc, 0.0 /* TODO */);

        loc = glGetUniformLocation(shader_id, "window_size");
        if (loc != -1) glUniform2f(loc, float(w[0]), float(w[1]));
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
