#pragma once
#include "context/context.hpp"
#include <map>
#include <chrono>
#include <list>

#include <armadillo>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum ButtonState {BTN_NULL, BTN_PRESSED, BTN_REPEATED, BTN_RELEASED};

/**
 * InputState - struct holding the state of button presses, cursor position, etc.
 */
struct InputState
{
    ButtonState up, left, down, right;
    ButtonState action, alternative, back;
    bool cursor_moved, zoomed;
    arma::vec2 cursor, zoom;
};

class Game;

/**
 * InputManager class - abstract class defining interface for getting input from devices.
 *
 * This class is to be derived from for each input method. It defines a consistent interface for input to enable
 * switching between input methods.
 *
 * The Game, in the input step in Game#run, first gets the active InputManager using get_active and then calls
 * handle_input to enact the input. In this method, the queued input is processed in order.
 */
class InputManager {
public:
    // Return the active input manager
    static InputManager *get_active();

    // Check game state - correct for input rate - and enact any input commands on the active InputContext
    void handle_input();

protected:
    void run_input_state(const InputState &input_state);

    std::list<InputState> _state_queue;
};