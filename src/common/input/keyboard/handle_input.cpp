#include "manager.hpp"
#include "../../game/game.hpp"

void KeyboardInputManager::handle_input()
{
    InputContext *context = this->get_context();

    if (glfwWindowShouldClose(this->get_window())) {
        context->back();
    }

    if (glfwGetKey(this->get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        context->back();
    }
}