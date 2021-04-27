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
 * Add Transform to the graveyard staging area. Due to the possibility that a event may exists which holds areference
 * to a destroyed Transform, the Transform is first detached from parent then added to this staging area. Then, when the
 * Event list is next empty (which should be within a few frames), the Transform is then deleted, and memory free'd.
 *
 * @param transform Transform to be deleted (when suitable).
 */
void Game::add_to_graveyard(Transform *transform)
{
    this->graveyard.push_back(transform);
}

/**
 * Run through the Events registered with the Game. If the event is ready (i.e. Event#check() returns true) then call
 * the Event#run() method.
 *
 * Events are removed from the game, and deleted, after being run. If there are no events, then transforms, if
 * requested, are deleted.
 *
 * \sa Game::add_to_graveyard
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

    if (this->events.empty()) {
        this->graveyard.sort();
        this->graveyard.unique();
        for (Transform *t : this->graveyard) {
            delete t;
        }
        this->graveyard.clear();
    }

}
