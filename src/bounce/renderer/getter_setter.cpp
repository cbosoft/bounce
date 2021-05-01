#include <bounce/renderer/renderer.hpp>
#include <bounce/game/game.hpp>

GLuint Renderer::get_varr() const
{
    return this->varr;
}

GLuint Renderer::get_vbuf() const
{
    return this->vbuf;
}

void Renderer::set_window_size(int w, int h)
{
    this->window_size[0] = w;
    this->window_size[1] = h;
    this->aspect_ratio = double(w)/double(h);
    this->game->get_active_scene()->get_active_camera()->set_aspect_preserve_diagonal(this->aspect_ratio);

    int scaled_w = int(this->window_size[0] * this->_window_scale[0]);
    int scaled_h = int(this->window_size[1] * this->_window_scale[1]);
    glViewport(0, 0, scaled_w, scaled_h);
}

int Renderer::get_fps() const
{
    return this->_actual_fps;
}

void Renderer::set_max_fps(int fps)
{
    this->_min_mspf = 1000/fps;
}

const arma::vec2 &Renderer::get_window_size() const
{
    return this->window_size;
}

void Renderer::set_window_name(const std::string &name) const
{
    const char *title_cstr = name.c_str();
    glfwSetWindowTitle(this->window, title_cstr);
}
