#include <bounce/event/destroy/destroy.hpp>

TransformDestroyEvent::TransformDestroyEvent(Transform *to_be_destroyed)
:   _to_be_destroyed(to_be_destroyed)
{
    // do nothing
}