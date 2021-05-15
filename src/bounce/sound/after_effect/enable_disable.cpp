#include <bounce/sound/after_effect/after_effect.hpp>
#include <bounce/sound/manager/manager.hpp>

void SoundAfterEffect::enable()
{
    SoundManager::ref().enable_effect(this);
}

void SoundAfterEffect::disable()
{
    SoundManager::ref().disable_effect(this);
}
