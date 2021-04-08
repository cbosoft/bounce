#include "renderer.hpp"

GLuint Renderer::get_shader(const std::string &name) const
{
   auto it = this->shaders.find(name);
   if (it != this->shaders.end()) {
       return it->second;
   }
   return -1;
}

GLuint Renderer::get_varr() const
{
    return this->varr;
}

GLuint Renderer::get_vbuf() const
{
    return this->vbuf;
}

const Transform *Renderer::get_camera_transform() const
{
    return &this->camera_transform;
}