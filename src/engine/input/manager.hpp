#pragma once
#include "context/context.hpp"
#include <map>
#include <chrono>
#include <armadillo>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * InputState - struct holding the state of button presses, cursor position, etc.
 */
struct InputState
{
    bool up, left, down, right;
    bool action, alternative, back;
    arma::vec2 cursor, zoom;
};

class Game;

/**
 * InputManager class - abstract class defining interface for getting input from devices.
 *
 * This class is to be derived from for each input method. It defines a  consistent interface for input so switching
 * between input methods.
 *
 * The Game, in the input step in Game#run, first gets the active InputManager using get_active and then calls
 * handle_input to enact the input - where input rate checking is performed and then the Game's active InputContext has
 * its action methods called depending on the InputState.
 */
class InputManager {
public:
    // Return the active input manager
    static InputManager *get_active();

    // Check game state - correct for input rate - and enact any input commands on the active InputContext
    void handle_input();

protected:
    /** Return the InputState - state of button presses etc - for the relevant device.
     * Abstract method to be overloaded by device specific sub-classes. */
    virtual InputState read_input_state() =0;

    bool check_input_rate(unsigned int key);

private:
    std::map<unsigned int, std::chrono::time_point<std::chrono::system_clock>> previous_press;
    InputState previous_state;
};