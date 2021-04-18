#include "manager.hpp"
#include "../../game/game.hpp"

InputState KeyboardInputManager::read_input_state()
{
    InputState rv = {false, false, false, false, false, false, false, {0, 0}, {0, 0}};
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

    double mouse_x, mouse_y;
    glfwGetCursorPos(this->get_window(), &mouse_x, &mouse_y);
    arma::vec2 w = Renderer::get().get_window_size();

    if (mouse_x < 0.0) mouse_x = 0.0;
    if (mouse_y < 0.0) mouse_y = 0.0;
    if (mouse_x > w[0]) mouse_x = w[0];
    if (mouse_y > w[1]) mouse_y = w[1];

    rv.cursor = arma::vec2{mouse_x, mouse_y};

    return rv;
}