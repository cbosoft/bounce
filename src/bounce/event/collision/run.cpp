#include <bounce/physics/collider/collider.hpp>
#include <bounce/event/collision/collision.hpp>

void CollisionEvent::run(Game *game)
{
    (void) game;
    this->_a->on_collision(this->_b);
    this->_b->on_collision(this->_a);
}