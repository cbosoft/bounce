#pragma once

#include "../settings.hpp"

class SoundAfterEffect {
public:
    SoundAfterEffect();
    virtual ~SoundAfterEffect();

    void enable();
    void disable();

    virtual void apply(AudioMonoBuffer &buffer) =0;
};