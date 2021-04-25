#include "manager.hpp"
#include "keyboard/manager.hpp"

InputManager * InputManager::get_active()
{
    static KeyboardInputManager &kb = KeyboardInputManager::ref();
    // TODO switch between keyboard and controller as necessary
    return &kb;
}