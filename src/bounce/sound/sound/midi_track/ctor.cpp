#include <bounce/sound/sound/midi_track/midi_track.hpp>

MidiTrack::MidiTrack(const MidiMessages &messages)
:   _tape_head{0}
,   _end{0}
,   _messages{messages}
{
    // initialise tones
    for (const auto &message : messages) {
        auto it = this->_tones.find(message.note);
        if (it == this->_tones.end()) {
            this->_tones[message.note] = new Tone(message.note, message.octave);
        }

        if (message.action == MIDI_ALL_STOP)
            this->_end = message.when;
    }

}