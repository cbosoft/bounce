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
    InputManager();

    static InputManager *get_active(Game *game);

    virtual InputState read_input_state() =0;

    InputContext *get_context() const;
    GLFWwindow *get_window() const;
    void handle_input();

private:

    void set_game(Game *game);

    bool check_input_rate(unsigned int key);

    std::map<unsigned int, std::chrono::time_point<std::chrono::system_clock>> previous_press;
    InputState previous_state;
    Game *_game;
};