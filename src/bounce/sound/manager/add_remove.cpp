#include <bounce/sound/manager/manager.hpp>

void SoundManager::add_sound(Sound *sound)
{
    this->_sounds.push_back(sound);
}

void SoundManager::remove_sound(Sound *sound)
{
    this->_sounds.remove(sound);
}