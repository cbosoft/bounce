#pragma once

#include <array>

#include <portaudio.h>

#include "../settings.hpp"

enum MusicNote {
    NOTE_A_FLAT,
    NOTE_A,
    NOTE_A_SHARP,
    NOTE_B_FLAT,
    NOTE_B,
    NOTE_C,
    NOTE_C_SHARP,
    NOTE_D_FLAT,
    NOTE_D,
    NOTE_D_SHARP,
    NOTE_E_FLAT,
    NOTE_E,
    NOTE_F,
    NOTE_F_SHARP,
    NOTE_G_FLAT,
    NOTE_G,
    NOTE_G_SHARP
};

class Sound {
public:
    Sound();
    virtual ~Sound();

    void play();
    void pause();
    bool is_playing() const;

    virtual Frame get_frame() =0;

    static float freq_from_note(MusicNote note, int octave);
private:
    bool _playing;
};
