#include <bounce/renderer/renderer.hpp>

/**
 * Tidies up stuff owned by the renderer.
 * - OpenGL stuff
 *
 * \todo tidy up shaders, textures etc
 * */
Renderer::~Renderer()
{
    glfwTerminate();
}