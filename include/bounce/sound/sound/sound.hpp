#pragma once

#include <array>

#include <portaudio.h>

#include "../settings.hpp"

class Sound {
public:
    Sound();
    virtual ~Sound();

    void play();
    void pause();
    bool is_playing() const;

    virtual Frame get_frame() =0;
private:
    bool _playing;
};
