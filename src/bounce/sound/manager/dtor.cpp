#include <bounce/sound/manager/manager.hpp>
#include <bounce/sound/sound/sound.hpp>
#include <bounce/sound/after_effect/after_effect.hpp>
#include <bounce/logging/logger.hpp>

SoundManager::~SoundManager()
{
    this->stop();

    for (auto *snd : this->_sounds) {
        delete snd;
    }

    for (auto *fx : this->_sound_after_effects) {
        delete fx;
    }

    PaError err = Pa_Terminate();
    if(err != paNoError) {
        Logger::ref() << LL_ERROR << "Error in sound teardown: " << Pa_GetErrorText(err) << "\n";
    }
}