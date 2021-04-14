#include "collision.hpp"

CollisionEvent::CollisionEvent(PhysicsObject *a, PhysicsObject *b)
:   _a(a)
,   _b(b)
{
    // do nothing
}