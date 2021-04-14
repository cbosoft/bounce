#include "collision.hpp"
#include "../../physics/object/object.hpp"

void CollisionEvent::run(Game *game)
{
    (void) game;
    this->_a->run_collision(this->_b);
    this->_b->run_collision(this->_a);
}