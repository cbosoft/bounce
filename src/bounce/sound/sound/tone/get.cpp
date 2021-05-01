#include <cmath>

#include <bounce/sound/sound/tone/tone.hpp>

Frame Tone::get_frame()
{
    Frame rv = {0};
    for (int i = 0; i < _SND_FRAME_SIZE; i++) {
        rv[i] = std::sin(this->freq*this->t)*0.2f;
        this->t += this->dt;
    }
    return rv;
}