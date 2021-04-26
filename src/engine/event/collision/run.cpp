#include "collision.hpp"
#include "../../object/object.hpp"

void CollisionEvent::run(Game *game)
{
    (void) game;
    this->_a->on_collision(this->_b);
    this->_b->on_collision(this->_a);
}