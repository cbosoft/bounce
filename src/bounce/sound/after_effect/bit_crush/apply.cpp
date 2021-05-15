#include <cmath>
#include <bounce/sound/after_effect/bit_crush/bit_crush.hpp>

void BitCrushAfterEffect::apply(AudioMonoBuffer &buffer)
{
    float m = 1.f/this->bin_size;
    for (int i = 0; i < (int)buffer.size(); i++) {
        buffer[i] = std::round(buffer[i]*m)*this->bin_size;
    }
}