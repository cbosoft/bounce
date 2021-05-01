#pragma once

#include <list>
#include <map>

#include "../sound.hpp"
#include "../tone/tone.hpp"

enum MidiAction {MIDI_START_NOTE, MIDI_STOP_NOTE, MIDI_ALL_STOP};

struct MidiMessage {
    MidiAction action;
    MusicNote note;
    int octave;
    long when;
};

typedef std::list<MidiMessage> MidiMessages;

class MidiTrack : public Sound {
public:
    MidiTrack(const MidiMessages &messages);

    Frame get_frame();

private:
    void do_action(const MidiMessage &message);

    long _tape_head, _end;
    MidiMessages _messages;
    std::map<MusicNote, Tone *> _tones;
};