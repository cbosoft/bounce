#pragma once
#include <list>

#include <portaudio.h>

#include "../settings.hpp"

class Sound;
class SoundManager {
public:
    static SoundManager &ref();
    ~SoundManager();

    void add_sound(Sound *sound);
    void remove_sound(Sound *sound);

    const Frame &get_frame();

private:
    void start();
    void stop();
    SoundManager();
    std::list<Sound *> _sounds;
    Frame _frame;
    PaStream *_stream;
};