#pragma once

class Game;
class Event {
public:
    virtual ~Event() =default;
    virtual bool check(Game *game) =0;
    virtual void run(Game *game) =0;
};

class ImmediateEvent : public Event {
public:
    bool check(Game *game) override { (void)game; return true; }
};