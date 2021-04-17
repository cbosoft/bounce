#include "manager.hpp"
#include "../../game/game.hpp"

InputState KeyboardInputManager::read_input_state()
{
    InputState rv = {false, false, false, false, false, false, false};
    auto *win = this->get_window();

#define KEYPRESSED(KEY) (glfwGetKey(win, KEY) == GLFW_PRESS)
#define MOUSEPRESSED(KEY) (glfwGetMouseButton(win, KEY) == GLFW_PRESS)

    if (KEYPRESSED(GLFW_KEY_UP)    || KEYPRESSED(GLFW_KEY_W)) { rv.up = true; }
    if (KEYPRESSED(GLFW_KEY_LEFT)  || KEYPRESSED(GLFW_KEY_A)) { rv.left = true; }
    if (KEYPRESSED(GLFW_KEY_DOWN)  || KEYPRESSED(GLFW_KEY_S)) { rv.down = true; }
    if (KEYPRESSED(GLFW_KEY_RIGHT) || KEYPRESSED(GLFW_KEY_D)) { rv.right = true; }
    if (KEYPRESSED(GLFW_KEY_F) || KEYPRESSED(GLFW_KEY_ENTER) || MOUSEPRESSED(GLFW_MOUSE_BUTTON_1)) { rv.action = true; }
    if (KEYPRESSED(GLFW_KEY_E) || KEYPRESSED(GLFW_KEY_P) || MOUSEPRESSED(GLFW_MOUSE_BUTTON_2))  { rv.alternative = true; }
    if (KEYPRESSED(GLFW_KEY_ESCAPE))  { rv.back = true; }


#undef KEYPRESSED

    return rv;
}