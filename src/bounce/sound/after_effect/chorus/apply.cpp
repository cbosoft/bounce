#include <bounce/sound/after_effect/chorus/chorus.hpp>

void ChorusAfterEffect::apply(AudioMonoBuffer &buffer)
{
    const auto s = (int)buffer.size();
    for (int i = 0; i < s; i++) {
        int j = (i + 5) % s;
        buffer[i] += buffer[j]*this->strength;
    }
}