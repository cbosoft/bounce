#include <iostream>

#include <bounce/sound/sound/midi_track/midi_track.hpp>

AudioMonoBuffer MidiTrack::get_mono_buffer()
{
    long next_end = this->_tape_head + long(_SND_BUFFER_SIZE);

    // if (next_end > this->_end) {
    //     this->pause();
    //     for (auto &kv : this->_tones) {
    //         kv.second->pause();
    //     }
    // }

    // process actions, update tones (start/stop)
    for (const auto &message : this->_messages) {
        if (message.when < next_end) {
            this->do_action(message);
        }
    }
    this->_tape_head = next_end;

    // generate a frame and return it
    //Frame frame = {0};
    //for (auto &kv : this->_tones) {
    //    Tone *tone = kv.second;
    //    if (tone->is_playing()) {
    //        const auto f = tone->get_frame();
    //        for (int i = 0; i < _SND_FRAME_SIZE; i++) {
    //            frame[i] += f[i];
    //        }
    //    }
    //}
    return AudioMonoBuffer{0};
}