#pragma once

#include "../after_effect.hpp"

class ChorusAfterEffect : public SoundAfterEffect {
public:
    explicit ChorusAfterEffect(float _strength);
    void apply(AudioMonoBuffer &buffer) override;

    float strength;
};