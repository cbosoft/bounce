#include "manager.hpp"
#include "../sound/sound.hpp"

const Frame &SoundManager::get_frame()
{
    this->_frame = {0};
    float n = 0.0;
    for (const auto &sound : this->_sounds) {
        if (sound->is_playing()) {
            auto f = sound->get_frame();
            for (int i = 0; i < _SND_FRAME_SIZE; i++) {
                this->_frame[i] += f[i];
            }
            n += 1.f;
        }
    }

    // for (int i = 0; i < _SND_FRAME_SIZE; i++) {
    //     this->_frame[i] /= n;
    // }

    return this->_frame;
}