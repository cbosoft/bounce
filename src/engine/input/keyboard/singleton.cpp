#include "manager.hpp"

KeyboardInputManager &KeyboardInputManager::ref()
{
    static KeyboardInputManager km;
    return km;
}