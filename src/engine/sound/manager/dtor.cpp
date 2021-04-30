#include "../../logging/logger.hpp"
#include "manager.hpp"

SoundManager::~SoundManager()
{
    PaError err = Pa_Terminate();
    if(err != paNoError) {
        Logger::ref() << LL_ERROR << "Error in sound teardown: " << Pa_GetErrorText(err) << "\n";
    }
}