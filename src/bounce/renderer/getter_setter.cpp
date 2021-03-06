#include <bounce/renderer/renderer.hpp>
#include <bounce/game/game.hpp>
#include <bounce/scene/scene.hpp>

/** @return the vertex array ID. */
GLuint Renderer::get_varr() const
{
    return this->varr;
}

/** @return the vertex buffer ID. */
GLuint Renderer::get_vbuf() const
{
    return this->vbuf;
}

/**
 * Set window size, given as width and height in pixels.
 *
 * This re-calculates the aspect ratio of the width and height and updates the scene camera. Finally, it rescales the
 * viewport.
 *
 * **Does not re-size window** - this is called when a window is resized to update information in renderer and scene.
 *
 * @param w Window width
 * @param h Window height
 */
void Renderer::set_window_size(int w, int h)
{
    this->window_size[0] = w;
    this->window_size[1] = h;
    this->aspect_ratio = double(w)/double(h);
    auto *cam = this->game->get_active_scene()->get_active_camera();
    arma::vec2 sz = cam->get_size();
    sz[0] = sz[1] * this->aspect_ratio;
    cam->set_size(sz);

    int scaled_w = int(this->window_size[0] * this->_window_scale[0]);
    int scaled_h = int(this->window_size[1] * this->_window_scale[1]);
    glViewport(0, 0, scaled_w, scaled_h);
}

/** @return Current fps. */
int Renderer::get_fps() const
{
    return this->_actual_fps;
}

/** Set the maximum allowed frame rate. */
void Renderer::set_max_fps(int fps)
{
    // max fps stored as minimum number of milliseconds between frame updates.
    this->_min_mspf = 1000/fps;
}

/** @return Current size of the window. */
const arma::vec2 &Renderer::get_window_size() const
{
    return this->window_size;
}

/** Update the window title. */
void Renderer::set_window_name(const std::string &name) const
{
    const char *title_cstr = name.c_str();
    glfwSetWindowTitle(this->window, title_cstr);
}
