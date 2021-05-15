#include <cmath>
#include <bounce/sound/after_effect/clip/clip.hpp>

void ClipAfterEffect::apply(AudioMonoBuffer &buffer)
{
    for (int i = 0; i < (int)buffer.size(); i++) {
        buffer[i] = (std::abs(buffer[i]) > 0.05f ? 0.05f : buffer[i]);
    }
}