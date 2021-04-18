#include "manager.hpp"

void KeyboardInputManager::mouse_btn_cb(GLFWwindow *win, int button, int action, int mods)
{
    KeyboardInputManager::ref().mouse_btn(win, button, action, mods);
}

void KeyboardInputManager::mouse_btn(GLFWwindow* window, int button, int action, int mods)
{
    bool v = action == GLFW_PRESS;

    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            this->_state.action = v;
            break;

        case GLFW_MOUSE_BUTTON_RIGHT:
            this->_state.alternative = v;
            break;

        default:
            break;
    }
}

void KeyboardInputManager::mouse_pos_cb(GLFWwindow *win, double x, double y)
{
    KeyboardInputManager::ref().mouse_pos(win, x, y);
}

void KeyboardInputManager::mouse_pos(GLFWwindow *win, double x, double y)
{
    (void) win;
    this->_state.cursor = {x, y};
}

void KeyboardInputManager::scroll_pos_cb(GLFWwindow *win, double x, double y)
{
    KeyboardInputManager::ref().scroll_pos(win, x, y);
}

void KeyboardInputManager::scroll_pos(GLFWwindow *win, double xoff, double yoff)
{
    (void) win;
    this->_state.zoom = {xoff, yoff};
}
