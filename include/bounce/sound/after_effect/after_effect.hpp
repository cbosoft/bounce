#pragma once

#include "../settings.hpp"

class SoundAfterEffect {
public:
    SoundAfterEffect();
    virtual ~SoundAfterEffect();

    void enable();
    void disable();
    void toggle();

    virtual void apply(AudioMonoBuffer &buffer) =0;

private:
    bool _enabled;
};