#include <bounce/sound/manager/manager.hpp>

void SoundManager::set_volume_mult(float volume)
{
    this->_volume_mult = volume;
}

float SoundManager::get_volume_mult() const
{
    return this->_volume_mult;
}