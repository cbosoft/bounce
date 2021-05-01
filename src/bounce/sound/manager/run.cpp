#include <bounce/logging/logger.hpp>
#include <bounce/sound/sound/sound.hpp>
#include <bounce/sound/manager/manager.hpp>

static int stream_run_callback(
        const void *input_buffer, void *output_buffer,
        unsigned long frames_per_buffer, const PaStreamCallbackTimeInfo* time_info,
        PaStreamCallbackFlags status_flags, void *user_data)
{
    auto *manager = (SoundManager *)user_data;
    auto *out = (float*)output_buffer;
    (void) input_buffer;
    (void) frames_per_buffer;
    (void) time_info;
    (void) status_flags;

    for (auto v : manager->get_frame()) {
        *(out++) = v;
        *(out++) = v;
    }

    return 0;
}

void SoundManager::start()
{
    /* Open an audio I/O stream. */
    PaError err = Pa_OpenDefaultStream(
            &this->_stream, 0, 2, paFloat32, _SND_SAMPLE_RATE, _SND_FRAME_SIZE, stream_run_callback, (void *)this);
    if (err != paNoError) {
        Logger::ref() << LL_ERROR << "Error initialising sound stream: " << Pa_GetErrorText(err) << "\n";
        throw std::runtime_error("could not init sound");
    }

    err = Pa_StartStream(this->_stream);
    if (err != paNoError) {
        Logger::ref() << LL_ERROR << "Error starting sound stream: " << Pa_GetErrorText(err) << "\n";
        throw std::runtime_error("could not init sound");
    }
}

void SoundManager::stop()
{
    PaError err = Pa_StopStream(this->_stream);
    if (err != paNoError) {
        Logger::ref() << LL_ERROR << "Error stopping sound stream: " << Pa_GetErrorText(err) << "\n";
        throw std::runtime_error("could not init sound");
    }
}
