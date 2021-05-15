#include <bounce/sound/manager/manager.hpp>
#include <bounce/sound/sound/sound.hpp>

const AudioBuffer &SoundManager::get_buffer()
{
    this->_buffer = {0};
    for (const auto &sound : this->_sounds) {
        if (sound->is_playing()) {
            auto f = sound->get_mono_buffer();

            for (auto *fx : this->_enabled_effects)
                fx->apply(f);

            const auto volume_mult = sound->get_volume_multiplier();

            float balance = (sound->get_lr_balance() + 1.f) * .5f;
            float left_mult = balance, right_mult = 1.f - balance;
            for (int i = 0; i < _SND_BUFFER_SIZE; i++) {
                // left
                this->_buffer[i*2] += f[i] * left_mult * volume_mult;
                // right
                this->_buffer[i*2 + 1] += f[i] * right_mult * volume_mult;
            }
        }
    }

    for (int i = 0; i < (int)this->_buffer.size(); i++)
        this->_buffer[i] = this->_buffer[i]*this->_volume_mult;

    return this->_buffer;
}