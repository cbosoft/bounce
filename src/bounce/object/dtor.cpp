#include <bounce/object/object.hpp>
#include <bounce/physics/engine/engine.hpp>

Object::~Object()
{
    PhysicsEngine::ref().unregister_object(this);
    Transform::~Transform();
}