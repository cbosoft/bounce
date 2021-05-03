#include <bounce/event/delayed/delayed.hpp>

TimeDelayedEvent::TimeDelayedEvent(long ms)
:   _ms(ms)
,   _from(EV_CLOCK_T::now())
{
    // do nothing
}

DelayRunOtherEvent::DelayRunOtherEvent(long ms, Event *payload)
:   TimeDelayedEvent(ms)
,   _payload(payload)
{

}