#include "destroy.hpp"
#include "../../physics/engine/engine.hpp"

void TransformDestroyEvent::run(Game *game)
{
    // tidying up is taken care of in dtor of transform/object etc
    delete this->_to_be_destroyed;
}