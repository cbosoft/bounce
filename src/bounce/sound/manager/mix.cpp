#include <bounce/sound/manager/manager.hpp>
#include <bounce/sound/sound/sound.hpp>

const AudioBuffer &SoundManager::get_buffer()
{
    this->_buffer = {0};
    for (const auto &sound : this->_sounds) {
        if (sound->is_playing()) {
            auto f = sound->get_mono_buffer();
            float bal = (sound->get_lr_balance() + 1.f)*.5f;
            float lmult = bal, rmult = 1.f - bal;
            for (int i = 0; i < _SND_BUFFER_SIZE; i++) {
                // left
                this->_buffer[i*2] += f[i]*lmult;
                // right
                this->_buffer[i*2 + 1] += f[i]*rmult;
            }
        }
    }

    return this->_buffer;
}