#include "renderer.hpp"

void Renderer::set_window_size(int w, int h)
{
  this->w = w;
  this->h = h;
  this->aspect_ratio = double(w)/double(h);
}

const Transform *Renderer::get_camera_transform() const
{
    return &this->camera_transform;
}

void Renderer::set_camera_target(Transform *t)
{
  this->camera_transform.set_parent(t);
}

void Renderer::set_camera_width(double width)
{
  this->camera_size[0] = width;
  this->camera_size[1] = width/this->aspect_ratio;
}

void Renderer::set_camera_height(double height)
{
  this->camera_size[0] = height*this->aspect_ratio;
  this->camera_size[1] = height;
}

void Renderer::set_camera_diagonal(double diagonal)
{
  // d*d = d2 = h*h + w*w;
  // w = ar*h
  // d2 = h*h + ar*ar*h*h;
  // d2 = h*h*(1 + ar*ar);
  // h = sqrt(d2/(1 + ar*ar))
  double h = std::sqrt(diagonal*diagonal / (1 + this->aspect_ratio*this->aspect_ratio));
  this->camera_size[0] = h*this->aspect_ratio;
  this->camera_size[1] = h;
}
