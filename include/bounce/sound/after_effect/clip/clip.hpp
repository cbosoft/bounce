#pragma once

#include "../after_effect.hpp"

class ClipAfterEffect : public SoundAfterEffect {
public:
    void apply(AudioMonoBuffer &buffer) override;
};