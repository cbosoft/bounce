#include <bounce/event/delayed/delayed.hpp>

bool TimeDelayedEvent::check(Game *game)
{
    (void) game;
    EV_TIME_PT_T now = EV_CLOCK_T::now();
    long dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_from).count();
    return (dt > this->_ms);
}