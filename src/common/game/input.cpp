#include "game.hpp"

void Game::input_step()
{
    auto window = this->renderer.get_window();
    this->should_quit = glfwWindowShouldClose(window) ||
            glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

    // TODO handle input
}
