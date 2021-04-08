#pragma once
#include "context/context.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Game;
class InputManager {
public:
    InputManager();

    static InputManager *get_active(Game *game);

    virtual void handle_input() =0;

    InputContext *get_context() const;
    GLFWwindow *get_window() const;

private:

    void set_game(Game *game);

    Game *_game;
};