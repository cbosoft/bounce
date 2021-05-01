#include <bounce/sound/sound/tone/tone.hpp>

Tone::Tone(float freq)
:   freq(freq)
,   t(0.0)
,   dt(1.f/float(_SND_SAMPLE_RATE))
{

}

Tone::Tone(MusicNote note, int octave)
:   Tone(Sound::freq_from_note(note, octave))
{

}