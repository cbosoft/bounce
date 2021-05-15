#include <bounce/sound/manager/manager.hpp>
#include <bounce/sound/sound/sound.hpp>
#include <bounce/sound/after_effect/after_effect.hpp>
#include <bounce/logging/logger.hpp>

SoundManager::~SoundManager()
{
    this->stop();

    auto sounds_copy = this->_sounds;
    for (auto *snd : sounds_copy) {
        delete snd;
    }

    auto fx_copy = this->_sound_after_effects;
    for (auto *fx : fx_copy) {
        delete fx;
    }

    PaError err = Pa_Terminate();
    if(err != paNoError) {
        Logger::ref() << LL_ERROR << "Error in sound teardown: " << Pa_GetErrorText(err) << "\n";
    }
}