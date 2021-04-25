#include "manager.hpp"

/**
 * @return Reference to KeyboardInputManager object.
 */
KeyboardInputManager &KeyboardInputManager::ref()
{
    static KeyboardInputManager km;
    return km;
}