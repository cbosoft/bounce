#include "game.hpp"

/**
 * Register an Event with the Game. The Event ptr is owned by the Game.
 *
 * In logic_step(), Events are executed (when ready).
 *
 * @param event The event to add.
 */
void Game::add_event(Event *event)
{
    this->events.push_back(event);
}

/**
 * Run through the Events registered with the Game. If the event is ready (i.e. Event#check() returns true) then call
 * the Event#run() method.
 *
 * Events are removed from the game, and deleted, after being run.
 */
void Game::logic_step()
{
    std::list<Event *> surviving_events;
    for (auto *event : this->events) {
        if (event->check(this)) {
            event->run(this);
            delete event;
        }
        else {
            surviving_events.push_back(event);
        }
    }
    this->events = surviving_events;
}
