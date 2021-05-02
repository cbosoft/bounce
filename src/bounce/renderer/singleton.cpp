#include <bounce/renderer/renderer.hpp>

/**
 * @return Reference to the Renderer singleton.
 */
Renderer &Renderer::get()
{
    static Renderer renderer;
    return renderer;
}