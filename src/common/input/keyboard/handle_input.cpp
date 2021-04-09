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

#define KEYPRESSED(KEY) (glfwGetKey(win, KEY) == GLFW_PRESS)

    if (KEYPRESSED(GLFW_KEY_UP)    || KEYPRESSED(GLFW_KEY_W)) { context->up(); }
    if (KEYPRESSED(GLFW_KEY_LEFT)  || KEYPRESSED(GLFW_KEY_A)) { context->left(); }
    if (KEYPRESSED(GLFW_KEY_DOWN)  || KEYPRESSED(GLFW_KEY_S)) { context->down(); }
    if (KEYPRESSED(GLFW_KEY_RIGHT) || KEYPRESSED(GLFW_KEY_D)) { context->right(); }

#undef KEYPRESSED

}