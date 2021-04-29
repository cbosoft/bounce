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

    ButtonState button_state = BTN_NULL;
    switch (action) {

        case GLFW_PRESS:
            button_state = BTN_PRESSED;
            break;

        case GLFW_REPEAT:
            button_state = BTN_REPEATED;
            break;

        case GLFW_RELEASE:
            button_state = BTN_RELEASED;
            break;

        default:
            return;
    }

    InputState new_state = {
            .up = BTN_NULL,
            .left = BTN_NULL,
            .down = BTN_NULL,
            .right = BTN_NULL,
            .action = BTN_NULL,
            .alternative = BTN_NULL,
            .back = BTN_NULL,
            .cursor_moved = false,
            .zoomed = false,
            .cursor = {0, 0},
            .zoom = {0, 0}
    };
    switch (key) {
        case GLFW_KEY_F:
        case GLFW_KEY_ENTER:
            new_state.action = button_state;
            break;

        case GLFW_KEY_UP:
        case GLFW_KEY_W:
            new_state.up = button_state;
            break;

        case GLFW_KEY_LEFT:
        case GLFW_KEY_A:
            new_state.left = button_state;
            break;

        case GLFW_KEY_DOWN:
        case GLFW_KEY_S:
            new_state.down = button_state;
            break;

        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            new_state.right = button_state;
            break;

        case GLFW_KEY_ESCAPE:
            new_state.back = button_state;
            break;

        default:
            // do nothing
            break;
    }

    this->_state_queue.push_back(new_state);
}