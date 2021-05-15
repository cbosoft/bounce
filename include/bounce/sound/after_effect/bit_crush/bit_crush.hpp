#pragma once

#include "../after_effect.hpp"

class BitCrushAfterEffect : public SoundAfterEffect {
public:
    explicit BitCrushAfterEffect(float _bin_size);
    void apply(AudioMonoBuffer &buffer);

    float bin_size;
};