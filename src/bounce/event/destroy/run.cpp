#include <bounce/physics/engine/engine.hpp>
#include <bounce/event/destroy/destroy.hpp>

void TransformDestroyEvent::run(Game *game)
{
    this->_to_be_destroyed->destroy();
}