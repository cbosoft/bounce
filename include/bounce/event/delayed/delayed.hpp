#pragma once

#include <chrono>
#include "../event.hpp"

typedef std::chrono::system_clock EV_CLOCK_T;
typedef EV_CLOCK_T::time_point EV_TIME_PT_T;

class TimeDelayedEvent : public Event {
public:
    explicit TimeDelayedEvent(long ms);

    bool check(Game *game) override;

private:
    long _ms;
    EV_TIME_PT_T _from;
};

class DelayRunOtherEvent : public TimeDelayedEvent {
public:
    DelayRunOtherEvent(long ms, Event *payload);

    void run(Game *game) override;

private:
    Event *_payload;
};