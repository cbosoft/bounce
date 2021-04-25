#pragma once
#include "context/context.hpp"
#include <map>
#include <chrono>
#include <armadillo>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct InputState
{
    bool up, left, down, right;
    bool action, alternative, back;
    arma::vec2 cursor, zoom;
};

class Game;
class InputManager {
public:

    static InputManager *get_active();

    void handle_input();

protected:
    virtual InputState read_input_state() =0;

    [[nodiscard]] InputContext *get_context() const;
    [[nodiscard]] GLFWwindow *get_window() const;

    bool check_input_rate(unsigned int key);

private:
    std::map<unsigned int, std::chrono::time_point<std::chrono::system_clock>> previous_press;
    InputState previous_state;
};