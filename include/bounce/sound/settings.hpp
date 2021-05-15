#pragma once

#include <array>

#define _SND_BUFFER_SIZE 256
#define _SND_SAMPLE_RATE 44100

typedef std::array<float, _SND_BUFFER_SIZE*2> AudioBuffer;
typedef std::array<float, _SND_BUFFER_SIZE> AudioMonoBuffer;
