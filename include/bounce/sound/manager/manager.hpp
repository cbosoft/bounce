#pragma once
#include <list>
#include <map>

#include <portaudio.h>
#include "../after_effect/after_effect.hpp"
#include "../settings.hpp"

class Sound;
class SoundManager {
public:
    static SoundManager &ref();
    ~SoundManager();

    void add_sound(Sound *sound);
    void remove_sound(Sound *sound);
    void add_effect(SoundAfterEffect *effect);
    void remove_effect(SoundAfterEffect *effect);

    void enable_effect(SoundAfterEffect *effect);
    void disable_effect(SoundAfterEffect *effect);

private:
    /* Private constructor, enforcing singleton */
    SoundManager();

    /* Launch sound thread */
    void start();

    /* Stop sound thread */
    void stop();

    /* Method to return a buffer of frames of sound samples.
     * The returned buffer is raveled left,right,left,right
     * for stereo. */
    const AudioBuffer &get_buffer();

    /* After effects */
    void distort();

    std::list<Sound *> _sounds;
    std::list<SoundAfterEffect *> _sound_after_effects;
    std::list<SoundAfterEffect *> _enabled_effects;
    AudioBuffer _buffer;
    PaStream *_stream;

    friend int stream_run_callback(
            const void *input_buffer, void *output_buffer,
            unsigned long frames_per_buffer, const PaStreamCallbackTimeInfo* time_info,
            PaStreamCallbackFlags status_flags, void *user_data);
};