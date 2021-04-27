#include "time_pause.hpp"

TemporaryTimePause::TemporaryTimePause(long length_ms)
:   _ms(length_ms)
{
    // do nothing
}

DelayedUnPause::DelayedUnPause(long length_ms)
:   TimeDelayedEvent(length_ms)
{
    // do nothing
}