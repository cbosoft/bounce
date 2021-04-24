#pragma once

#include "../manager.hpp"

class KeyboardInputManager : public InputManager {
public:
    static KeyboardInputManager &ref();
    InputState read_input_state() override;

private:
    KeyboardInputManager();

    void key_press(GLFWwindow *win, int key, int scancode, int action, int mods);
    void mouse_btn(GLFWwindow *win, int button, int action, int mods);
    void mouse_pos(GLFWwindow *win, double x, double y);
    void scroll_pos(GLFWwindow *win, double xoff, double yoff);

    static void key_press_cb(GLFWwindow *win, int key, int scancode, int action, int mods);
    static void mouse_btn_cb(GLFWwindow *win, int button, int action, int mods);
    static void mouse_pos_cb(GLFWwindow *win, double x, double y);
    static void scroll_pos_cb(GLFWwindow *win, double xoff, double yoff);

    InputState _state;

};