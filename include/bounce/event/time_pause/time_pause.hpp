#pragma once

#include "../event.hpp"
#include "../delayed/delayed.hpp"

class TemporaryTimePause : public ImmediateEvent
{
public:
    TemporaryTimePause(long length_ms);

    void run(Game *game) override;

private:
    long _ms;
};


class DelayedUnPause : public TimeDelayedEvent
{
public:
    DelayedUnPause(long length_ms);

    void run(Game *game) override;
};