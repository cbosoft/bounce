#include <bounce/input/keyboard/manager.hpp>

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
            .cursor = {0., 0.},
            .zoom = {0., 0.}
    };
    switch (key) {
        case GLFW_KEY_F:
            new_state.char_state = button_state;
            new_state.ch = 'f';
            /* fallthrough */
        case GLFW_KEY_ENTER:
            new_state.action = button_state;
            break;

        case GLFW_KEY_W:
            new_state.char_state = button_state;
            new_state.ch = 'w';
            /* fallthrough */
        case GLFW_KEY_UP:
            new_state.up = button_state;
            break;

        case GLFW_KEY_A:
            new_state.char_state = button_state;
            new_state.ch = 'a';
            /* fallthrough */
        case GLFW_KEY_LEFT:
            new_state.left = button_state;
            break;

        case GLFW_KEY_S:
            new_state.char_state = button_state;
            new_state.ch = 's';
            /* fallthrough */
        case GLFW_KEY_DOWN:
            new_state.down = button_state;
            break;

        case GLFW_KEY_D:
            new_state.char_state = button_state;
            new_state.ch = 'd';
            /* fallthrough */
        case GLFW_KEY_RIGHT:
            new_state.right = button_state;
            break;

        case GLFW_KEY_ESCAPE:
            new_state.back = button_state;
            break;

        case GLFW_KEY_1:
            new_state.char_state = button_state;
            new_state.ch = '1';
            break;

        case GLFW_KEY_2:
            new_state.char_state = button_state;
            new_state.ch = '2';
            break;

        case GLFW_KEY_3:
            new_state.char_state = button_state;
            new_state.ch = '3';
            break;

        case GLFW_KEY_4:
            new_state.char_state = button_state;
            new_state.ch = '4';
            break;

        case GLFW_KEY_5:
            new_state.char_state = button_state;
            new_state.ch = '5';
            break;

        case GLFW_KEY_6:
            new_state.char_state = button_state;
            new_state.ch = '6';
            break;

        case GLFW_KEY_7:
            new_state.char_state = button_state;
            new_state.ch = '7';
            break;

        case GLFW_KEY_8:
            new_state.char_state = button_state;
            new_state.ch = '8';
            break;

        case GLFW_KEY_9:
            new_state.char_state = button_state;
            new_state.ch = '9';
            break;

        case GLFW_KEY_0:
            new_state.char_state = button_state;
            new_state.ch = '0';
            break;

        case GLFW_KEY_Q:
            new_state.char_state = button_state;
            new_state.ch = 'q';
            break;

        case GLFW_KEY_E:
            new_state.char_state = button_state;
            new_state.ch = 'e';
            break;

        case GLFW_KEY_R:
            new_state.char_state = button_state;
            new_state.ch = 'r';
            break;

        case GLFW_KEY_T:
            new_state.char_state = button_state;
            new_state.ch = 't';
            break;

        case GLFW_KEY_Y:
            new_state.char_state = button_state;
            new_state.ch = 'y';
            break;

        case GLFW_KEY_U:
            new_state.char_state = button_state;
            new_state.ch = 'u';
            break;

        case GLFW_KEY_I:
            new_state.char_state = button_state;
            new_state.ch = 'i';
            break;

        case GLFW_KEY_O:
            new_state.char_state = button_state;
            new_state.ch = 'o';
            break;

        case GLFW_KEY_P:
            new_state.char_state = button_state;
            new_state.ch = 'p';
            break;

        case GLFW_KEY_LEFT_BRACKET:
            new_state.char_state = button_state;
            new_state.ch = '[';
            break;

        case GLFW_KEY_RIGHT_BRACKET:
            new_state.char_state = button_state;
            new_state.ch = ']';
            break;

        case GLFW_KEY_G:
            new_state.char_state = button_state;
            new_state.ch = 'g';
            break;

        case GLFW_KEY_H:
            new_state.char_state = button_state;
            new_state.ch = 'h';
            break;

        case GLFW_KEY_J:
            new_state.char_state = button_state;
            new_state.ch = 'j';
            break;

        case GLFW_KEY_K:
            new_state.char_state = button_state;
            new_state.ch = 'k';
            break;

        case GLFW_KEY_L:
            new_state.char_state = button_state;
            new_state.ch = 'l';
            break;

        case GLFW_KEY_Z:
            new_state.char_state = button_state;
            new_state.ch = 'z';
            break;

        case GLFW_KEY_X:
            new_state.char_state = button_state;
            new_state.ch = 'x';
            break;

        case GLFW_KEY_C:
            new_state.char_state = button_state;
            new_state.ch = 'c';
            break;

        case GLFW_KEY_V:
            new_state.char_state = button_state;
            new_state.ch = 'v';
            break;

        case GLFW_KEY_B:
            new_state.char_state = button_state;
            new_state.ch = 'b';
            break;

        case GLFW_KEY_N:
            new_state.char_state = button_state;
            new_state.ch = 'n';
            break;

        case GLFW_KEY_M:
            new_state.char_state = button_state;
            new_state.ch = 'm';
            break;

        case GLFW_KEY_SPACE:
            new_state.char_state = button_state;
            new_state.ch = ' ';
            break;

        case GLFW_KEY_MINUS:
            new_state.char_state = button_state;
            new_state.ch = '-';
            break;

        case GLFW_KEY_EQUAL:
            new_state.char_state = button_state;
            new_state.ch = '=';
            break;

        case GLFW_KEY_SEMICOLON:
            new_state.char_state = button_state;
            new_state.ch = ';';
            break;

        case GLFW_KEY_COMMA:
            new_state.char_state = button_state;
            new_state.ch = ',';
            break;

        case GLFW_KEY_PERIOD:
            new_state.char_state = button_state;
            new_state.ch = '.';
            break;

        case GLFW_KEY_GRAVE_ACCENT:
            new_state.char_state = button_state;
            new_state.ch = '`';
            break;

        default:
            // do nothing
            break;
    }

    this->_state_queue.push_back(new_state);
}