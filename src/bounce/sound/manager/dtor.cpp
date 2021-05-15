#include <bounce/sound/manager/manager.hpp>
#include <bounce/logging/logger.hpp>

SoundManager::~SoundManager()
{
    this->stop();

    PaError err = Pa_Terminate();
    if(err != paNoError) {
        Logger::ref() << LL_ERROR << "Error in sound teardown: " << Pa_GetErrorText(err) << "\n";
    }
}