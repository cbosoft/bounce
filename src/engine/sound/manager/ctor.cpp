#include "manager.hpp"
#include "../../logging/logger.hpp"

SoundManager::SoundManager()
: _stream{nullptr}
{
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        Logger::ref() << LL_ERROR << "Error initialising sound manager: " << Pa_GetErrorText(err) << "\n";
        throw std::runtime_error("could not init sound");
    }

    this->start();
}