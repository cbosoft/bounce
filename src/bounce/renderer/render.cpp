#include <bounce/renderer/renderer.hpp>
#include <bounce/physics/engine/engine.hpp>
#include <bounce/game/game.hpp>
#include <bounce/scene/scene.hpp>

/** @return Current GLFW window. Used when dealing with input. */
GLFWwindow  *Renderer::get_window()
{
    return this->window;
}

/**
 * Check if the a render pass is required at all based on the time since the previous render. This calculates and
 * enforces frame rate.
 *
 * @return Whether the render should go ahead. */
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

/**
 * Main call which renders the scene.
 *
 * First checks if the render is needed by checking Renderer::should_render. Then, the current active scene is updated
 * (by calling the Scene::update method). After, the scenes which need to be rendered are gathered and passed to
 * Renderer::render_scene.
 *
 * Scenes which need rendering may not just be the active scene. Scenes can be "insubstantial" which essentially means
 * it has no background and is intended to be rendered on the backdrop of a previous scene. This is useful for drawing a
 * menu atop some gameplay (for example, in a pause menu or conversation).
 *
 * Once the scenes are rendered, any screen effects are applied. Then, finally, the freame is rendered to screen.
 *
 * \sa Scene::is_insubstantial
 * \sa Renderer::render_scene
 */
void Renderer::render()
{
    if (!this->should_render()) {
        return;
    }

    // Call update action on transforms in active scene.
    this->game->get_active_scene()->update();

    this->set_target_to_texture(this->txt);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(this->varr);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbuf);

    int w, h;
    glfwGetWindowSize(this->window, &w, &h);
    this->set_window_size(w, h);

    for (const Scene *scene :this->game->get_scenes_to_be_rendered()) {
        this->render_scene(scene);
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

/**
 * Render scene. This gets a list of Renderable(s) in the scene and draws them. The Renderable(s) are drawn in order of
 * their z value. The Renderable actually handles its own drawing - Renderable::draw.
 *
 * \sa Renderable::get_z
 * \sa Renderable::set_z
 *
 * @param scene
 */
void Renderer::render_scene(const Scene *scene)
{
    if (scene) {
        this->update_shader_uniforms(scene->get_active_camera());

        // draw zsorted renderables
        std::list<const Renderable *> rbls;
        scene->get_renderables(rbls);
        rbls.sort(Renderable::z_sort);
        for (auto *rbl : rbls) {
            if (rbl && rbl->get_visible())
                rbl->draw();
        }
    }
}