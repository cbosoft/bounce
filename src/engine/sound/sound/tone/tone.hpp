#pragma once

#include "../sound.hpp"

class Tone : public Sound {
public:
    Tone (float freq);

    Frame get_frame();

private:
    float freq, t, dt;
};