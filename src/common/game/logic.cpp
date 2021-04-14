#include "game.hpp"

void Game::add_event(Event *event)
{
    this->events.push_back(event);
}

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

    for (auto *object : this->get_active_scene()->get_objects()) {
        object->update();
    }
}
