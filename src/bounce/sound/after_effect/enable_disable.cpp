#include <bounce/sound/after_effect/after_effect.hpp>
#include <bounce/sound/manager/manager.hpp>

void SoundAfterEffect::enable()
{
    this->_enabled = true;
    SoundManager::ref().enable_effect(this);
}

void SoundAfterEffect::disable()
{
    this->_enabled = false;
    SoundManager::ref().disable_effect(this);
}

void SoundAfterEffect::toggle()
{
    if (this->_enabled) {
        this->disable();
    }
    else {
        this->enable();
    }
}
