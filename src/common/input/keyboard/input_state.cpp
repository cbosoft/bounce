#include "manager.hpp"
#include "../../game/game.hpp"

InputState KeyboardInputManager::read_input_state()
{
    return this->_state;
}