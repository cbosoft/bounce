#include "renderer.hpp"

arma::vec2 Renderer::world_pt_to_screen_pt(arma::vec2 pt)
{
    pt = pt - this->camera_transform.get_position();
    //pt = pt % this->window_size;
    pt = pt / this->camera_size;
    //pt = pt + this->window_size*0.5;
    //pt[1] = this->window_size[0] - pt[1];
    return pt;
}

double Renderer::world_len_to_screen_len(double l)
{
    //l *= this->window_size[0];
    l /= this->camera_size[0];
    return l;
}

void Renderer::set_camera_target(Transform *t)
{
    this->camera_transform.set_parent(t);
}
