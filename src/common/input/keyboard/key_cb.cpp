#include "manager.hpp"

void KeyboardInputManager::key_press_cb(GLFWwindow *win, int key, int scancode, int action, int mode)
{
    KeyboardInputManager::ref().key_press(win, key, scancode, action, mode);
}

void KeyboardInputManager::key_press(GLFWwindow *win, int key, int scancode, int action, int mode)
{
    (void) win;
    (void) scancode;
    (void) mode;

    bool v = action == GLFW_PRESS || action == GLFW_REPEAT;

    switch (key) {
        case GLFW_KEY_F:
        case GLFW_KEY_ENTER:
            this->_state.action = v;
            break;

        case GLFW_KEY_UP:
        case GLFW_KEY_W:
            this->_state.up = v;
            break;

        case GLFW_KEY_LEFT:
        case GLFW_KEY_A:
            this->_state.left = v;
            break;

        case GLFW_KEY_DOWN:
        case GLFW_KEY_S:
            this->_state.down = v;
            break;

        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            this->_state.right = v;
            break;

        case GLFW_KEY_ESCAPE:
            this->_state.back = v;
            break;

        default:
            // do nothing
            break;
    }
}