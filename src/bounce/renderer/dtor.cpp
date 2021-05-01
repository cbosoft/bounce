#include <bounce/renderer/renderer.hpp>

Renderer::~Renderer()
{
    glfwTerminate();
}