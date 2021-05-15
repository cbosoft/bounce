#include <cmath>

#include <bounce/sound/sound/tone/tone.hpp>

AudioMonoBuffer Tone::get_mono_buffer()
{
    AudioMonoBuffer rv = {0};
    for (int i = 0; i < _SND_BUFFER_SIZE; i++) {
        rv[i] = std::sin(this->freq*this->t);
        this->t += this->dt;
    }
    return rv;
}