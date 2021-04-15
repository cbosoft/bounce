#include "renderer.hpp"
#include "../physics/engine/engine.hpp"
#include "../game/game.hpp"

GLFWwindow  *Renderer::get_window()
{
    return this->window;
}

void Renderer::render()
{
    auto now = _RDR_CLOCK_T::now();
    auto time_since = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->time_last_render);
    int us = int(time_since.count());
    if (us < this->_min_mspf) {
        return;
    }
    this->_actual_fps = (this->_actual_fps + (1000/us))/2;
    this->time_last_render = now;

    auto *active = this->game->get_active_scene();
    active->on_update();
    for (auto *object : active->get_objects()) {
        object->update();
    }

    int w, h;
    glfwGetWindowSize(this->window, &w, &h);
    this->set_window_size(w, h);

    // high dpi displays scale up contents; need to take that into accound.
    float xscale, yscale;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    w = int(float(w)*xscale);
    h = int(float(h)*yscale);

    glViewport(0, 0, w, h);

    this->update_shader_uniforms();
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);

    glBindTexture(GL_TEXTURE_2D, this->txt);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0,
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
    Scene *scene = this->game->get_active_scene();
    if (scene) {
        std::vector<Renderable *> rbls = scene->get_floating_renderables();
        for (auto *object : scene->get_objects()) {
            auto *rbl = object->get_renderable();
            if (rbl) rbls.push_back(rbl);
        }
        std::sort(rbls.begin(), rbls.end(), Renderable::z_sort);
        for (auto *rbl : rbls) {
            if (rbl && rbl->get_visible())
                rbl->draw();
        }
    }

    // draw quad to screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    arma::vec2 position = camera->get_position(), size = camera->get_size();
    for (const auto &kv : this->shaders) {
        GLuint shader_id = kv.second;
        glUseProgram(shader_id);
        int loc = glGetUniformLocation(shader_id, "time");
        if (loc != -1) glUniform1f(loc, float(PhysicsEngine::engine().get_time()));

        loc = glGetUniformLocation(shader_id, "camera_position");
        auto cp = position;
        if (loc != -1) glUniform2f(loc, float(cp[0]), float(cp[1]));

        loc = glGetUniformLocation(shader_id, "camera_size");
        auto cs = size;
        if (loc != -1) glUniform2f(loc, float(cs[0]), float(cs[1]));

        loc = glGetUniformLocation(shader_id, "camera_angle");
        if (loc != -1) glUniform1f(loc, 0.0 /* TODO */);
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
