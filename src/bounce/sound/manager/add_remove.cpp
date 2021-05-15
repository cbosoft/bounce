#include <bounce/sound/manager/manager.hpp>

void SoundManager::add_sound(Sound *sound)
{
    this->_sounds.push_back(sound);
}

void SoundManager::remove_sound(Sound *sound)
{
    this->_sounds.remove(sound);
}

void SoundManager::add_effect(SoundAfterEffect *effect)
{
    this->_sound_after_effects.push_back(effect);
}

void SoundManager::remove_effect(SoundAfterEffect *effect)
{
    this->_sound_after_effects.remove(effect);
}

void SoundManager::enable_effect(SoundAfterEffect *effect)
{
    this->_enabled_effects.push_back(effect);
}

void SoundManager::disable_effect(SoundAfterEffect *effect)
{
    this->_enabled_effects.remove(effect);
}