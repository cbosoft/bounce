#include "renderer.hpp"

static Renderer *_renderer_singleton = nullptr;

Renderer &Renderer::init(int w, int h, const std::string &title)
{
    _renderer_singleton = new Renderer(w, h, title);
    return *_renderer_singleton;
}

Renderer &Renderer::get()
{
    return *_renderer_singleton;
}