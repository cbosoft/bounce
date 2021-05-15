#pragma once

#include "../sound.hpp"

class Tone : public Sound {
public:
    explicit Tone(float freq);
    Tone(MusicNote note, int octave);

    AudioMonoBuffer get_mono_buffer() override;

private:
    float freq, t, dt;
};