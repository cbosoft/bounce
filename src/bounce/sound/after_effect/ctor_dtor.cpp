#include <bounce/sound/after_effect/after_effect.hpp>
#include <bounce/sound/manager/manager.hpp>

SoundAfterEffect::SoundAfterEffect()
:   _enabled(false)
{
    SoundManager::ref().add_effect(this);
}

SoundAfterEffect::~SoundAfterEffect()
{
    SoundManager::ref().remove_effect(this);
}