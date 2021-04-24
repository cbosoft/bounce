#include "object.hpp"
#include "../physics/engine/engine.hpp"

Object::~Object()
{
    PhysicsEngine::ref().unregister_object(this);
    Transform::~Transform();
}