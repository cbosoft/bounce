#include "manager.hpp"

/**
 * @return Copy of cached InputState.
 */
InputState KeyboardInputManager::read_input_state()
{
    return this->_state;
}