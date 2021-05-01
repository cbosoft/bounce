#include <bounce/sound/sound/sound.hpp>
#include <bounce/sound/manager/manager.hpp>

Sound::Sound()
:   _playing{false}
{
    SoundManager::ref().add_sound(this);
}

Sound::~Sound()
{
    SoundManager::ref().remove_sound(this);
}

void Sound::play()
{
    this->_playing = true;
}

void Sound::pause()
{
    this->_playing = false;
}

bool Sound::is_playing() const
{
    return this->_playing;
}