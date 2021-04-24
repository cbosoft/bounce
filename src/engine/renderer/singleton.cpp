#include "renderer.hpp"

Renderer &Renderer::get()
{
    static Renderer renderer;
    return renderer;
}