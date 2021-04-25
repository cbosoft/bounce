#include "manager.hpp"
#include "keyboard/manager.hpp"

/**
 * Placeholder - only KeyboardInputManager currently implemented!
 *
 * \todo Implement controller and alternative control schemes
 * \todo Figure out how best to determine which input method is active
 *
 * @return Currently active input manager
 */
InputManager * InputManager::get_active()
{
    static KeyboardInputManager &kb = KeyboardInputManager::ref();
    // TODO switch between keyboard and controller as necessary
    return &kb;
}