#pragma once

#include <array>

#define _SND_FRAME_SIZE 256
#define _SND_SAMPLE_RATE 44100

typedef std::array<float, _SND_FRAME_SIZE> Frame;