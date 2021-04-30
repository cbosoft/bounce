#include "manager.hpp"

SoundManager &SoundManager::ref()
{
    static SoundManager sm;
    return sm;
}