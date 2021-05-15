#pragma once
#include <list>
#include <map>

#include <portaudio.h>

#include "../settings.hpp"

class Sound;
class SoundManager {
public:
    static SoundManager &ref();
    ~SoundManager();

    void add_sound(Sound *sound);
    void remove_sound(Sound *sound);

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

    std::list<Sound *> _sounds;
    AudioBuffer _buffer;
    PaStream *_stream;

    friend int stream_run_callback(
            const void *input_buffer, void *output_buffer,
            unsigned long frames_per_buffer, const PaStreamCallbackTimeInfo* time_info,
            PaStreamCallbackFlags status_flags, void *user_data);
};