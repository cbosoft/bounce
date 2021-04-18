#include "object.hpp"
#include "../physics/engine/engine.hpp"

Object::~Object()
{
    PhysicsEngine::engine().unregister_object(this);
    Transform::~Transform();
}