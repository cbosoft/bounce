#include <bounce/event/collision/collision.hpp>

CollisionEvent::CollisionEvent(Collider *a, Collider *b)
:   _a(a)
,   _b(b)
{
    // do nothing
}