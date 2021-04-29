#include "manager.hpp"

void KeyboardInputManager::mouse_btn_cb(GLFWwindow *win, int button, int action, int mods)
{
    KeyboardInputManager::ref().mouse_btn(win, button, action, mods);
}

void KeyboardInputManager::mouse_btn(GLFWwindow* window, int button, int action, int mods)
{
    (void) window;
    (void) mods;

    ButtonState button_state = BTN_NULL;
    switch (action) {
        case GLFW_PRESS:
            button_state = BTN_PRESSED;
            break;

        case GLFW_RELEASE:
            button_state = BTN_RELEASED;
            break;

        case GLFW_REPEAT:
            button_state = BTN_REPEATED;
            break;

        default:
            break;
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
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            new_state.action = button_state;
            break;

        case GLFW_MOUSE_BUTTON_RIGHT:
            new_state.alternative = button_state;
            break;

        default:
            break;
    }
    this->_state_queue.push_back(new_state);
}

void KeyboardInputManager::mouse_pos_cb(GLFWwindow *win, double x, double y)
{
    KeyboardInputManager::ref().mouse_pos(win, x, y);
}

void KeyboardInputManager::mouse_pos(GLFWwindow *win, double x, double y)
{
    (void) win;
    this->_state_queue.push_back({
            .up = BTN_NULL,
            .left = BTN_NULL,
            .down = BTN_NULL,
            .right = BTN_NULL,
            .action = BTN_NULL,
            .alternative = BTN_NULL,
            .back = BTN_NULL,
            .cursor_moved = true,
            .zoomed = false,
            .cursor = {x, y},
            .zoom = {0, 0}
    });
}

void KeyboardInputManager::scroll_pos_cb(GLFWwindow *win, double x, double y)
{
    KeyboardInputManager::ref().scroll_pos(win, x, y);
}

void KeyboardInputManager::scroll_pos(GLFWwindow *win, double xoff, double yoff)
{
    (void) win;
    this->_state_queue.push_back({
        .up = BTN_NULL,
        .left = BTN_NULL,
        .down = BTN_NULL,
        .right = BTN_NULL,
        .action = BTN_NULL,
        .alternative = BTN_NULL,
        .back = BTN_NULL,
        .cursor_moved = false,
        .zoomed = true,
        .cursor = {0, 0},
        .zoom = {xoff, yoff}
    });
}
