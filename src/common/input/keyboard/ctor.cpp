#include "manager.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

KeyboardInputManager::KeyboardInputManager()
: _state({false, false, false, false, false, false, false, {0, 0}, {0, 0}})
{
    glfwSetKeyCallback(this->get_window(), KeyboardInputManager::key_press_cb);
    glfwSetMouseButtonCallback(this->get_window(), KeyboardInputManager::mouse_btn_cb);
    glfwSetCursorPosCallback(this->get_window(), KeyboardInputManager::mouse_pos_cb);
    glfwSetScrollCallback(this->get_window(), KeyboardInputManager::scroll_pos_cb);
}