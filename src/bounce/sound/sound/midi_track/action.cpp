#include <bounce/sound/sound/midi_track/midi_track.hpp>

void MidiTrack::do_action(const MidiMessage &message)
{
    Tone *tone = this->_tones[message.note];
    switch (message.action) {
        case MIDI_START_NOTE:
            tone->play();
            break;
        case MIDI_STOP_NOTE:
            tone->pause();
            break;
        case MIDI_ALL_STOP:
            for (auto &kv : this->_tones)
                kv.second->pause();
            this->pause();
            break;
    }
}