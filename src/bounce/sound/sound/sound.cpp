#include <cmath>

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

float Sound::freq_from_note(MusicNote note, int octave)
{
    float pwr = 0.f;
    const float a4 = 440.f;
    switch (note) {
        case NOTE_A_FLAT:  pwr = -1.f; break;
        case NOTE_A:       pwr =  0.f; break;
        case NOTE_A_SHARP: /* fallthrough */
        case NOTE_B_FLAT:  pwr =  1.f; break;
        case NOTE_B:       pwr =  2.f; break;
        case NOTE_C:       pwr =  3.f; break;
        case NOTE_C_SHARP: /* fallthrough */
        case NOTE_D_FLAT:  pwr =  4.f; break;
        case NOTE_D:       pwr =  5.f; break;
        case NOTE_D_SHARP: /* fallthrough */
        case NOTE_E_FLAT:  pwr =  6.f; break;
        case NOTE_E:       pwr =  7.f; break;
        case NOTE_F:       pwr =  8.f; break;
        case NOTE_F_SHARP: /* fallthrough */
        case NOTE_G_FLAT:  pwr =  9.f; break;
        case NOTE_G:       pwr = 10.f; break;
        case NOTE_G_SHARP: pwr = 11.f; break;
    }

    auto foctave = float(octave);
    float freq = a4 * std::pow(2.f, pwr/12.f + foctave - 4.f);

    return freq;
}