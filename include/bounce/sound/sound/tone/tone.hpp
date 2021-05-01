#pragma once

#include "../sound.hpp"

class Tone : public Sound {
public:
    Tone(float freq);
    Tone(MusicNote note, int octave);

    Frame get_frame();

private:
    float freq, t, dt;
};