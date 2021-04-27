#include "destroy.hpp"
#include "../../physics/engine/engine.hpp"

void TransformDestroyEvent::run(Game *game)
{
    this->_to_be_destroyed->destroy();
}