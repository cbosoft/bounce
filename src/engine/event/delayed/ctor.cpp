#include "delayed.hpp"

TimeDelayedEvent::TimeDelayedEvent(long ms)
:   _ms(ms)
,   _from(EV_CLOCK_T::now())
{
    // do nothing
}