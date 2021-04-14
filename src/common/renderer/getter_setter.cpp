#include "renderer.hpp"
#include "../game/game.hpp"

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
}
