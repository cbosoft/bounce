#include <bounce/event/delayed/delayed.hpp>
#include <bounce/game/game.hpp>

void DelayRunOtherEvent::run(Game *game)
{
    game->add_event(this->_payload);
}