#include <iostream>
#include <bounce/sound/after_effect/after_effect.hpp>
#include <bounce/sound/manager/manager.hpp>

void SoundAfterEffect::enable()
{
    std::cerr << "ENABLE" << std::endl;
    SoundManager::ref().enable_effect(this);
}

void SoundAfterEffect::disable()
{
    SoundManager::ref().disable_effect(this);
}
