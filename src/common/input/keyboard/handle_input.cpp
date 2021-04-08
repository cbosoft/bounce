#include "manager.hpp"
#include "../../game/game.hpp"

void KeyboardInputManager::handle_input()
{
    InputContext *context = this->get_context();
    auto *win = this->get_window();

    if (
            glfwWindowShouldClose(this->get_window()) ||
            glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        context->back();
    }

    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)  { context->left(); }
    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) { context->right(); }
    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)    { context->up(); }
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)  { context->down(); }

}