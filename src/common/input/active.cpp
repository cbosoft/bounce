#include "manager.hpp"
#include "keyboard/manager.hpp"

InputManager * InputManager::get_active(Game *game)
{
    static KeyboardInputManager &kb = KeyboardInputManager::ref();
    kb.set_game(game);
    // TODO switch between keyboard and controller as necessary
    return &kb;
}