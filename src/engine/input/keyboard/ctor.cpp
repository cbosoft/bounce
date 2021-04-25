#include "manager.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../renderer/renderer.hpp"

/**
 * Constructor: registers GLFW callbacks and initialises the input state to zero/no action.
 */
KeyboardInputManager::KeyboardInputManager()
: _state({false, false, false, false, false, false, false, {0, 0}, {0, 0}})
{
    GLFWwindow *win = Renderer::get().get_window();
    glfwSetKeyCallback(win, KeyboardInputManager::key_press_cb);
    glfwSetMouseButtonCallback(win, KeyboardInputManager::mouse_btn_cb);
    glfwSetCursorPosCallback(win, KeyboardInputManager::mouse_pos_cb);
    glfwSetScrollCallback(win, KeyboardInputManager::scroll_pos_cb);
}